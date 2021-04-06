#include "data.h"
#include "memmacros.h"

// template instantiation
CREATE_BOXING_FOR(struct drawing_context_t, boxed_draw);
CREATE_BOXING_FOR(struct computation_context_t, boxed_comp);
CREATE_BOXING_FOR(struct packed_args_t, boxed_args);
CREATE_BOXING_FOR(struct binded_widget_t, boxed_bind);
CREATE_BOXING_FOR(atomic_bool, boxed_atomic_bool);
