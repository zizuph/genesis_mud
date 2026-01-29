inherit "std/container";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"

#define GEM_DIR "/d/Genesis/gems/obj/"

string bot_types() 
{
    string *bottles =
                 ({"bot_red", "bot_clear", "bot_green"});
    return ONE_OF_LIST(bottles);
}

void reset_container()
{
//    switch (random(3))
//    {
//        case 0:
//        case 1:
//            break;
//        case 2:
            setuid();
            seteuid(getuid());

            clone_object("/d/Shire/eastroad/obj/" + bot_types())->move(TO);
//            break;
//        default:
//            break;
//    }
}

void
create_container()
{
   set_short("heap of trash");
   set_name("heap");
   add_name(({"trash","trash heap","heap"}));
   add_adj(({"of trash","trash heap","trash"}));
   set_long("This is a heap of trash that has been dropped down the well. It looks disgusting and smells horrible.\n");

   add_prop(CONT_I_VOLUME, 19000);
   add_prop(CONT_I_MAX_VOLUME, 25000); /* Can't put much here */
   add_prop(CONT_I_WEIGHT, 38000000);   /*Heavy heap */
   add_prop(CONT_I_MAX_WEIGHT, 40000000);
   add_prop(OBJ_I_VALUE, 17);
   add_prop(CONT_I_RIGID, 1); /* Heaps are kinda rigid. ;) */

    enable_reset();
    reset_container();
}
