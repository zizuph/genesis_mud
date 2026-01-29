// The guild object of the Old Fogey's Club...Dunstable 12/94

// used to shadow player and give out the new guild object.
// this will be removed after everyone has had a chance to chage over
//Glaurung 8-97

#pragma save_binary;

inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include "/d/Shire/common/defs.h"
#define FOGEY_SOUL OBJ_DIR+"club/fogey_soul"
#define RACE this_player()->query_race()


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
    object shadow;

    ::init();

    setuid(); seteuid(getuid());
    shadow = clone_object("/d/Shire/common/obj/club/fogey_shadow");
    shadow->shadow_me(ENV(TO));
    TO->remove_object();
}
