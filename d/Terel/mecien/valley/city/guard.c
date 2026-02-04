inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>

#define STAND_DIR "/d/Terel/mecien/valley/city/"

create_monster(){
::create_monster();
set_name("guard", "knight");
set_adj("town");
add_name("human");
set_race_name("guard");
set_short("city guard");
set_long("He keeps the peace here in the city.\n");
set_base_stat(SS_INT, 15);
set_base_stat(SS_WIS, 15);
set_base_stat(SS_DIS, 15);
set_base_stat(SS_STR, 40);
set_base_stat(SS_DEX, 40);
set_base_stat(SS_CON, 55);
set_skill(SS_WEP_POLEARM, 65);
set_skill(SS_PARRY, 50);
set_skill(SS_DEFENCE, 50);
set_hp(10000);
set_alignment(300);

set_all_hitloc_unarmed(10);

add_prop(OBJ_I_WEIGHT, 100000);
add_prop(OBJ_I_VOLUME, 100000);
add_prop(CONT_I_MAX_WEIGHT, 140000);
add_prop(CONT_I_MAX_VOLUME, 140000);
seq_new("do_things");
seq_addfirst("do_things", "@@equip_me");
}

init_living(){
::init_living();
check_criminal();
}

check_criminal(){
object *room_list;
int i;

if(this_object()->query_enemy()) return;

room_list = all_inventory(environment(this_object()));
for (i=0; i<sizeof(room_list);i++)
   if(living(room_list[i]))
    {
      if(room_list[i]->query_prop("criminal"))
      {
    this_object()->command("shout Halt!");
   room_list[i]->catch_msg(QCTNAME(this_object()) + " attacks you!\n");
   tell_room(environment(this_object()), QCTNAME(this_object()) + 
    " attacks " + room_list[i]->query_name() + "!\n", room_list[i]);
      this_object()->attack_object(room_list[i]);
      }
   }

}



equip_me(){
object halberd, armour, armour2, money;
seteuid(getuid(this_object()));
halberd=clone_object(STAND_DIR+"halberd");
halberd->move(this_object());
command("wield halberd");
armour=clone_object(STAND_DIR+"hauberk");
armour->move(this_object());
command("wear hauberk");
armour2=clone_object(STAND_DIR+"helmet");
armour2->move(this_object());
command("wear helmet");
money=MONEY_MAKE_SC(20);
money->move(this_object());
}
