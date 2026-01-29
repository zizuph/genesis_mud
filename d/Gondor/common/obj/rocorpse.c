/*
 * Am not sure who coded this object, but it has been in the game since
 * at least 1994, so my guess it's likely Elessar. I cleaned up the code
 * and got it ready for a quest.
 * Finwe, February 2018
 */

inherit "/std/container";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define GEM_DIR "/d/Genesis/gems/obj/"

string gem_types() 
{
    string *gemtypes =
                 ({"agate", "amber", "amethyst", "beryl_red",
                   "chalcedony", "coral", "diamond", "emerald", "garnet", 
                   "jade", "opal", "pearl_black", "pearl", "peridot", 
                   "ruby", "sapphire", "topaz_yellow", "topaz", "moonstone"});
    return one_of_list(gemtypes);
}

void reset_container()
{
    switch (random(3))
    {
        case 0:
        case 1:
            break;
        case 2:
            setuid();
            seteuid(getuid());

            clone_object("/d/Genesis/gems/obj/" + gem_types())->move(this_object());
            break;
        default:
            break;
    }
}

void
create_container()
{
    seteuid(getuid(this_object()));
    set_name("corpse");
    add_name("rohrrim","corpse of a rohirrim");
    set_adj("mutilated");
    set_adj("beheaded");
    set_short("corpse of a rohirrim");
    set_pshort("corpses of rohirrim");
    set_long("This is the dead body of a Rohirrim. It has been horribly " +
        "mutilated. The man has been killed in flight with several sword " +
        "cuts from behind. Blood is all over him, and most noticably, his " +
        "head is missing. Since the blood is not dry yet, it looks like " +
        "he was massacred quite recently.\n");
    add_prop(CONT_I_IN,1);
    add_prop(CONT_I_WEIGHT,80000);
    add_prop(CONT_I_VOLUME,100000);
    add_prop(CONT_I_MAX_WEIGHT,80000);
    add_prop(CONT_I_MAX_VOLUME,100000);

    enable_reset();
    reset_container();
}
