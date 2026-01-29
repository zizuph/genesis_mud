// The guild object of the Old Fogey's Club...Dunstable 12/94

#pragma save_binary;

inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include "/d/Shire/common/defs.h"
#define FOGEY_SOUL OBJ_DIR+"club/fogey_soul"
#define RACE this_player()->query_race_name()


void
create_object()
{
        set_name("cane");
        add_name("_fogey_cane_");
        add_adj(({"old","gnarled"}));
        set_short("old gnarled cane");
        set_long("This old gnarled cane is made of the sternest of oak, "+
        "which withstands the test of time very well.  The epitaph "+
        "'fhelp' has been etched into the side.\n");
        add_prop(OBJ_I_WEIGHT, 20);
        add_prop(OBJ_I_VOLUME, 100);
        add_prop(OBJ_I_VALUE, 0);
        add_prop(OBJ_M_NO_DROP,"The cane grips your hand and will not "+
        "let go.\n");
}

void
init()
{
   ::init();

    if(TP->query_gender() != 0 && TP->query_wiz_level() < 1 &&
    RACE != "hobbit" && RACE != "human" && RACE != "dwarf")
 {
     write("You aren't an Old Fogey anymore!\n");
     write("Your cane disintegrates into dust.\n");
      remove_object();
     }

   set_alarm(3.0, 0.0, "get_me_soul", TP);
}

string
query_auto_load() { return "/d/Shire/common/obj/club/cane:"; }

void
get_me_soul(object ob)
{
  int i;
  string *souls;

      seteuid(getuid());
      souls = ob->query_cmdsoul_list();
      for (i = 0; i < sizeof(souls); i++)
      ob->remove_cmdsoul(souls[i]);

      ob->add_cmdsoul(FOGEY_SOUL);
      for(i = 0; i < sizeof(souls); i++)
      if(souls[i] != FOGEY_SOUL)
      ob->add_cmdsoul(souls[i]);
      ob->update_hooks();
}


