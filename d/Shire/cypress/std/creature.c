/*  We just inherit the std creature for now... maybe some day down the
 *  road we'll develop this creature  -Igneous-
 *  Converted to Cypress
 *  -- Finwe, June 2001
 */

inherit "/std/creature.c";
inherit "/std/combat/unarmed.c";

void create_shire_creature() {}

nomask void
create_creature()
{

    create_shire_creature();
}
