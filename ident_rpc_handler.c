#if 0
(
set -xeu
exec gcc -Ic_modules -std=gnu11 -Wall -Wextra -Werror -DSIMPLE_LOGGING -o /dev/null $(find -name '*.c') -lpthread
)
exit 0
#endif
#include <keystore/keystore.h>
#include "ident_rpc_handler.h"

const struct io_handler ident_handler = {
	.type = DATA_IDENT_REQ,
	.func = ident_handle,
	.arg = NULL
};

static const char *node_description;

void ident_init(const char *description)
{
	node_description = description;
}

enum io_handler_result ident_handle(struct io_intf *io, const struct relay_packet *p, void *arg)
{
	(void) arg;
	if (strcmp(p->type, DATA_IDENT_REQ) != 0) {
		return iohr_ignore;
	}
	struct keystore ms;
	keystore_init(&ms, 100, 100);
	keystore_append(&ms, REG_IDENT_NAME, p->local);
	if (node_description != NULL) {
		keystore_append(&ms, REG_IDENT_DESC, node_description);
	}
	size_t res_len;
	const char *res_data = keystore_data(&ms, &res_len);
	io_intf_send(io, DATA_IDENT_RES, p->remote, res_data, res_len);
	return iohr_handled;
}
