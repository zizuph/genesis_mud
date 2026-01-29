inherit "/std/monster";
#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
#include <macros.h>
#include <money.h>
#include <language.h>
void
create_monster() {
   set_name("drinker");
   set_race_name("wyrmman");
   set_adj(ONE_OF_LIST(({"large","small","muscular",
               "shifty-eyed","evil-eyed","black-skinned","scrawny"})));
   set_adj(ONE_OF_LIST(({"drunk","swaggering","drooling",
               "cantankerous","raucous","dark","blathering"})));
   set_long("This fellow just seems to be here to " +
      "relax and enjoy himself.  He's pretty rowdy.\n");
   set_gender(0);
   set_aggressive(0);
   default_config_mobile(ONE_OF_LIST(({ 25, 35, 45, 55, 65 })));
   set_hp(100);
   set_alignment(ONE_OF_LIST(({ -50, -75, -100, -125 })));
   set_skill(SS_DEFENCE, (ONE_OF_LIST(({ 30, 45, 60 }))));
   set_skill(SS_PARRY, (ONE_OF_LIST(({ 20, 30, 40 }))));
   set_skill(SS_UNARM_COMBAT, (ONE_OF_LIST(({ 25, 35, 45 }))));
   set_skill(SS_WEP_SWORD, (ONE_OF_LIST(({ 30, 40, 50 }))));
   set_skill(SS_WEP_CLUB, (ONE_OF_LIST(({ 25, 35, 45, 55 }))));
   set_skill(SS_WEP_KNIFE, (ONE_OF_LIST(({ 10, 30, 90 }))));
   set_skill(SS_WEP_AXE, (ONE_OF_LIST(({ 1, 30, 60, 70 }))));
   set_act_time(ONE_OF_LIST(({ 0, 4, 6 })));
   add_act(({"buy grog","drink grog"}));
   add_act(({"buy wine","drink wine"}));
   add_act(({"emote walks over to you","emote peers oddly at you",
            "emote mutters:  You'shiz deerunk!"}));
   add_act("shout Another of rounds for this table!");
   add_act("emote slams his drink down on the table " +
      "spilling grog all about.");
   add_act("emote sings: I'eeell seeeng yo oh sto reeeeee!");
   add_act(({"emote glares about stonily, his head wobbly.",
            "emote passes out in his bowl of boar intestines."}));
   add_act("emote belches and a piece of boar intestines spills out.");
   add_act("emote beats his friend across the face.");
   add_act("emote falls flat on his back as his chair collapses.");
   add_act("emote puts his arm around you and drunkenly spills some Meat wine down your neck");
   add_act("shout Chang! Chang! Chang! Chang!  and slams " +
      "down his grog");
   set_alarm(1.0,0.0,"get_stuff");
}
get_stuff() {
   int i;
   object ob1;
   seteuid(getuid());
   ob1 = MONEY_MAKE(ONE_OF_LIST(({
               1,2,3,4,10 })),ONE_OF_LIST(({"copper","silver","gold"})))->move(TO);
   clone_object(ONE_OF_LIST(({
               "/d/Rhovanion/mute/dungeon1/waxe2.c",
               "/d/Rhovanion/mute/dungeon1/wwarhammer3.c",
               "/d/Rhovanion/mute/dungeon1/wsword3.c",
               "/d/Rhovanion/mute/dungeon1/wknife2.c",
               "/d/Rhovanion/mute/dungeon1/loincloth.c"})))->move(TO);
   clone_object(ONE_OF_LIST(({
               "/d/Rhovanion/mute/dungeon1/wshirt.c",
               "/d/Rhovanion/mute/dungeon1/wshirt2.c",
               "/d/Rhovanion/mute/dungeon1/whelmet2.c"})))->move(TO);
   clone_object(ONE_OF_LIST(({
               "/d/Rhovanion/mute/dungeon1/wpants.c",
               "/d/Rhovanion/mute/dungeon1/loincloth.c",
               "/d/Rhovanion/mute/dungeon1/wpants3.c"})))->move(TO);
   command("wear all");
   command("wield all");
   return 1;
}
