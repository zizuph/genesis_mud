
// file name: /d/Avenir/common/park/obj/maquahuitl_r.c
// creator(s): Ilyian (14 March, 1995)
// last update:
// purpose: To be wielded by the Guardian creature in
//            /d/Avenir/common/park/dlord.c
//          Same as /d/Avenir/common/park/obj/maquahuitl_l.c, just a
//            different hand and wield message
// note: It is a _very_ good weapon (35/34), with the severe drawback that it
//       dulls quite easily (set_likely_dull(50) )
// bug(s):
// to-do:

inherit "/std/weapon";
#include "/d/Avenir/common/common.h"
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"
#include <macros.h>

create_weapon(){
    set_name("maquahuitl");
    add_name("sword");
    set_adj("nasty");
    add_adj("black");
    set_short("nasty black maquahuitl");
    set_long("This nasty weapon is actually a flat stave of very "
            +"hard wood as long as a human's arm. Along both edges "
            +"of it's length are inset flakes of razor sharp "
            +"obsidian. The sword's handle, also wooden, is quite "
            +"long, probably to offset the weight of the heavy blade. "
            +"While this weapon would probably break quite quickly "
            +"against an enemy's armour, it looks like it would do "
            +"quite a bit of damage beforehand.\n");

    set_hit(35);
    set_pen(34);
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    set_hands(W_RIGHT);
    set_likely_dull(50);
    set_likely_corr(0);
    set_likely_break(8);

    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 1323);

    set_wf(this_object());
}

wield(){
      write("The weight of the "+short()+" feels strange in your "
           +"hand. You twirl it around a bit to get the feel.\n");
      say(QCTNAME(this_player()) + " twirls the "+short()
           +" around.\nAn eerie, high pitched moan emanates from the "
           +short()+".\n");
      return 0;
}

void
init()
 {
   ::init();
    add_action("swing_func", "swing");
 }

int
swing_func(string arg)
 {
    string str;   

    if(arg == "maquahuitl")
     {     
      write(
"You swing the "+short()+" through the air with a mighty sweep.\n"+
"The "+short()+" makes a piercing shriek as it cuts through the air.\n");
      say(
QCTNAME(this_player()) + " swings the "+short()+" through the air.\n"+
"The "+short()+" produces a piercing shriek.\n");
   return 1;
     }
      notify_fail("Swing what ?\n");
 }


