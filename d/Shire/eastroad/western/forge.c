#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/room";

#include "local.h"

#define MY_SHOVEL ("/d/Shire/common/obj/shovel")
#define MY_KNIFE ("/d/Shire/common/weapon/sell_knife")
#define MY_AXE ("/d/Shire/common/weapon/sell_axe")
#define MY_SWORD ("/d/Shire/common/weapon/sell_sword")
#define MY_BAND ("/d/Shire/common/obj/iron_band")

object weapon;
static object bill, blacksmith;

void
create_room() 
{
   set_short("smithy");
   set_long("The heat in this smithy is almost unbearable. You wonder "
         + "how the blacksmith can work in these circumstances. The blacksmith "
         /*  + "is capable of straightening bent weapons and " */
         + "sells some tools and weapons here. "
         + "A little sign is hanging on the wall.\n");
   
   add_item(({"sign","little sign"}),"@@sign_long");
   
   add_exit (EAST_R_DIR + "lpath1","northwest",0,1);
   
   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
   reset_shire_room();
}

void
reset_shire_room() 
{
   if (!blacksmith)
   {  
     blacksmith = clone_object("/d/Shire/common/monster/blacksmith");
     blacksmith->move(this_object());
   }
   
   /* addition made by merrygrin */
/*   
   if (!bill) 
   {
     bill = clone_object("/d/Shire/common/monster/son_of_smith");
     bill->move(this_object());
   }
*/   
   if (!present("iron"))
      clone_object("/d/Shire/common/obj/cast_iron")->move(this_object());
}

void
init() 
{
   ::init();
   add_action("do_read","read",0);
   add_action("forge_band","forge");
}

string
sign_long() 
{
   int p1, p2, p3, p4,p5;
   
   seteuid(getuid());
   p1 = MY_SHOVEL->query_prop(OBJ_I_VALUE) * 2;
   p2 = MY_KNIFE->query_prop(OBJ_I_VALUE) * 2;
   p3 = MY_AXE->query_prop(OBJ_I_VALUE) * 2;
   p4 = MY_SWORD->query_prop(OBJ_I_VALUE) * 2;
   p5 = MY_BAND->query_prop(OBJ_I_VALUE) * 2;
   
   return 
     "Shovel . . . . . . . .  " + p1 + " copper coins\n" +
     "Long knife . . . . . .  " + p2 + " copper coins\n" +
     "Sturdy axe . . . . . .  " + p3 + " copper coins\n" +
     "Mediocre sword . . . .  " + p4 + " copper coins\n" +
//     "Iron band. . . . . . .  " + p5 + " copper coins\n" +
   /*
   + "Weapon improvement:\n"
   + "-------------------\n"
   + "Harden <weapon>  . . . . . xx  copper coins\n"
   + "Sharpen <weapon> . . . . . xx  copper coins\n"
   + "Straighten <weapon>  . . . xx  copper coins\n"
   */
   "\n";
}

int
do_read(string str) 
{
   if (str == "sign" || str == "little sign")
      {
      write("You read:\n" + sign_long());
      return 1;
   }
   return 0;
}


int
forge_band(string str) 
{

    if(str == "band" || str == "patch" || str == "iron band" || str == "iron patch")
    {
        write("you forge the iron patch.\n");
        return 1;
    }

    NF("Forge what, an iron band?\n");
    return 0;


}