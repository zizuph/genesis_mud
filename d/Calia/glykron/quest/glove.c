inherit "/std/armour";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

int wear(object ob){
 write(
  "As you wear the bracelet, it feels like you are slipping on a glove.\n"
  +"In addition, your hand now seems to be invisible!\n"); 
 return 0;
}

int remove(object ob){
 object ob2;
 if((ob2=present("intang_sword", environment(ob))) && ob2->query_wielded())
  this_player()->command("drop hiltless sword");
 write("You can see your hand again as you remove the bracelet.\n");
 return 0;
}

create_armour(){
 set_name(({"glove","invis_glove","bracelet"}));
 set_adj("cloth");
 set_short("cloth bracelet");
 set_long(
  "When the cloth bracelet is turned one way, it looks normal.  However, when\n"
  +"it is turned the other way, there is darkness through the hole.\n");
 set_ac(50);
 set_at(A_R_ARM);
 set_am(({0, 0, 0}));
 set_af(this_object());
 add_prop(OBJ_I_WEIGHT, 1000);
 add_prop(OBJ_I_VOLUME, 1000);
}
