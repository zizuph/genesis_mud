inherit "std/container";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"

#define GEM_DIR "/d/Genesis/gems/obj/"

string gem_types() 
{
    string *gemtypes =
                 ({"agate", "amber", "amethyst", "beryl_red",
                   "chalcedony", "coral", "diamond", "emerald", "garnet", 
                   "jade", "opal", "pearl_black", "pearl", "peridot", 
                   "ruby", "sapphire", "topaz_yellow", "topaz", "moonstone"});
    return ONE_OF_LIST(gemtypes);
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

            clone_object("/d/Genesis/gems/obj/" + gem_types())->move(TO);
            break;
        default:
            break;
    }
}

void
create_container()
{
   set_short("heap of rubble");
   set_name("heap");
   add_name(({"rubble","rubble heap","pile","stone"}));
   add_adj(({"of rubble","rubble","stone"}));
   set_long("This is a heap of battered-down stones, and "+
   "they seem to have been battered as much by time as "+
   "violence.\n");

   add_prop(CONT_I_VOLUME, 19000);
   add_prop(CONT_I_MAX_VOLUME, 25000); /* Can't put much here */
   add_prop(CONT_I_WEIGHT, 38000000);   /*Heavy rock */
   add_prop(CONT_I_MAX_WEIGHT, 40000000);
   add_prop(OBJ_I_VALUE, 17);
   add_prop(CONT_I_RIGID, 1); /* Heaps are kinda rigid. ;) */

    enable_reset();
    reset_container();
}
