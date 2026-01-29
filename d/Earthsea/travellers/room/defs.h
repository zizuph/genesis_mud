#ifndef SECURE_DEFINED
#include <std.h>
#endif

#define IS_WIZ(x) (SECURITY->query_wiz_rank(x->query_real_name()) > 0)
#define IS_ARCH(x) (SECURITY->query_wiz_rank(x->query_real_name()) >= WIZ_ARCH)
#define EARTHSEA_WIZ(x) \
    (SECURITY->query_wiz_dom(x->query_real_name()) == "Earthsea")
