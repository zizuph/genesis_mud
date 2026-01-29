#include "../default.h"
inherit GHOST_BASE;

void
create_hero()
{
   set_name("warrior");
    add_name("_ghost_warrior_");
    add_name("_ghost_warrior");
   set_adj("ghost");
   set_short("ghost warrior");
   set_long("This is the ghost of a valiant warrior "+
      "who died ages ago fighting evil. He rises once "+
      "again to fulfill his ancient vow.\n");

   default_config_npc(70 + random(40));

   set_combat_skills(55 + random(25));
   set_alignment(random(500) + 100);
}
