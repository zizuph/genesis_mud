inherit "/std/weapon";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"
#include <macros.h>

create_weapon(){
    set_name("maquahuitl");
    add_name("sword");
    set_adj("vicious");
    add_adj("black");
    set_short("vicious black maquahuitl");
    set_long("This nasty weapon is actually a flat stave of very "
            +"hard wood as long as a human's arm. Along both edges "
            +"of it's length are inset flakes of razor sharp "
            +"obsidian. The sword's handle, also wooden, is quite "
            +"long, probably to offset the weight of the heavy blade. "
            +"While this weapon would probably break quite quickly "
            +"against an enemy's armour, it looks like it would do "
            +"quite a bit of damage beforehand.\n");

    set_hit(35);
    set_pen(18);
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    set_hands(W_LEFT);
    set_likely_dull(80);
    set_likely_corr(0);
    set_likely_break(10);

//    add_prop(OBJ_I_WEIGHT, );
//    add_prop(OBJ_I_VOLUME, );
    add_prop(OBJ_I_VALUE, 1323);
  
    set_wf(this_object());
}

wield(){
      write("The weight of the maquahuitl feels strange in your "
           +"hand. You give it a test swing through the air, and "
           +"it sends out an eerie low hum.\n");
      say(QCTNAME(this_player()) + " swings the maquahuitl "
           +"through the air, and it send out a loud and low pitched "
           +"hum that sends shivers down your spine.\n");
      return 0;
}
