#pragma once
/* Handler for IDENT commands - pass through even if handled, for pipelines */
#include <stdbool.h>
#include <io/io.h>

#include "ident_rpc.h"

void ident_init(const char *description);

enum io_handler_result ident_handle(struct io_intf *io, const struct relay_packet *p, void *arg);

extern const struct io_handler ident_handler;
