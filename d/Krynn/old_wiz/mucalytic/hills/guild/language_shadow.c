/* Language (layman) guild shadow. ~mucalytic/hills/guild/language_shadow */

inherit "/std/guild/guild_lay_sh";

#include "../defs.h"

int query_guild_tax_lay()
{
    return 2; // 2% tax
}

string query_guild_style_lay()
{
    return "language";
}

string query_guild_name_lay()
{
    return LANGUAGE_GUILD;
}
