/* 
 * /d/Kalad/common/wild/pass/kaldoro/wep/pet_club.c
 * Purpose    : Sprokter's club.  It's magical. 
 * Located    : ../npc/sprokter.c
 * Created By : Rico 15.Dec.94
 * Modified By: 
 */ 

inherit "/d/Kalad/std/weapon";

#include "/d/Kalad/defs.h"

int uses = 3;

create_weapon()
{
   ::create_weapon();

   set_name("club");
   set_adj("petrified");
   add_adj("powerful");

   set_short("petrified powerful club");
   set_long("@@my_long");

   add_item(({ "knot","small knot" }),
      "This knot juts out from near the tip of the "+
      "club. It is rather sharp and nasty looking. "+
      "If caught by it, it could most definately do "+
      "some nasty damage to your body.\n");
   set_hit(50);
   set_pen(35);

   set_wt(W_CLUB);
   set_dt(W_SLASH | W_BLUDGEON);
   set_wf(TO);
   add_prop(OBJ_I_VALUE,2500);
   add_prop(OBJ_I_WEIGHT,25000);
   add_prop(OBJ_I_VOLUME,25000);
   add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
   add_prop(OBJ_S_WIZINFO,("This is an enchanted club, giving it "+
      "a better hit and bludgeon than normal weapons. To wield "+
      "the club, the wielder must have str > 99, dis > 99, "+
      "45 or better in the club skill and 25 or better in the "+
      "spellcraft skill. In addition, because of its large "+
      "size, no hobbits or gnomes may wield it. The club can "+
      "be commanded to expend a portion of its power to heal "+
      "its possesor. By typing 'command aamrfgk', the "+
      "wielder will be healed physically. However, the club "+
      "can only do this three times before losing its "+
      "healing power. This weapon can be found on Kleater's "+
      "buddy, Sprokter.\n"));
   add_prop(MAGIC_AM_ID_INFO,
      ({"The club is magically enchanted.\n", 5,
      "The axe has been magically enchanted to hit "+
         "and bludgeon more.\n", 25,
      "The enchanted axe has greater hit and "+
         "bludgeon than normal weapons and has "+
         "several unique abilities. Failure to "+
         "wield it will result in bodily harm.\n", 55}));
   add_prop(MAGIC_AM_MAGIC, "enchantment", 45);
}

string
my_long()
{
   string empty_desc;
   if(uses < 1)
      empty_desc = "You can feel vibrations emanating from it.";
   else
      empty_desc = "You receive a small shock when ou try to "+
         "touch it.";
   return("This is an amazing club, you wonder how it "+
      "was crafted. No doubt by dwarven smiths. This club "+
      "is of petrified redwood. It has what looks like a "+
      "knot on one side of it near the tip. You bet it "+
      "could tear a nice chunk of your flesh away. "+
      "Wha a weapon indeed! It is obviously very "+
      "powerful. Now, if only you can get your paws "+
      "on it... " + empty_desc + "\n");
}

mixed
wield(object what)
{
   if(TP->query_base_stat(SS_STR) > 99)
      if(TP->query_base_stat(SS_DIS) > 99)
      if(TP->query_skill(SS_WEP_CLUB) > 44)
      if(TP->query_skill(SS_SPELLCRAFT) > 24)
      if(TP->query_race_name() != "hobbit")
      if(TP->query_race_name() != "gnome") 
      {
      write("With a tremendous strain and mental effort, "+
         "you are barely able to gain control of the "+
         "club. You are able to make out a cry of agony "+
         "which seems to emanate from the within the "+
         "club.\n");
      say(QCTNAME(TP) + "'s eyes glaze over "+
         "as " + TP->query_pronoun() + " attempts "+
         "to gain control of the powerful club.\n");
      set_alarm(10.0,0.0,"club");
      return 0;
   }
   TP->heal_hp(-800);
   say(QCTNAME(TP) + "'s life-force is slowly being ebbed "+
      "away by the petrified club!\n");
   if(TP->query_hp() <= 0)
      TP->do_die(TO);
   return("Try as you might, you just aren't strong enough "+
      "to control the club. You can hear a wailing of triuph "+
      "emanating from within the club. You can feel your "+
      "very essence being sucked away!\n");
}

club(object ob)
{
   write("say You feel the hunger within the club. It screams "+
      "at you with an amazing strength: Feed me!!\n");
   say(QCTNAME(TP) + " gets a horrified expression.\n");
   TP->command("shout I detest the foul Hobbits!!!");
   TP->command("spit");
   TP->catch_msg("You search for the nearest hobbit "+
      "who will make up your next meal...\n");
   TP->command("kill hobbit");
   set_alarm(50.0, 0.0, "fortify");
   return 1;
}

mixed
unwield(object what)
{
   return 0;
}

init()
{
   ::init();

   add_action("impress", "impress");
   add_action("cpound", "cpound");
   add_action("fortify", "fortify");
   add_action("command", "command");
}

impress()
{
   if(!query_wielded(TO))
      {
      write("You must wield the club first.\n");
      return 1;
   }
   write("You skillfully twirl the club through the air "+
      "over your head!\n");
   say(QCTNAME(TP) + " skillfully twirls the club through "+
      "the air above " + TP->query_pronoun() + " head!\n");
   TP->command("cackle demonically");
   return 1;
}

cpound()
{
   if(!query_wielded(TO))
   {
      write("You must wield the club first.\n");
      return 1;
   }
   write("You grasp the petrified club firmly with both "+
      "of your hands and raise it above your head. With "+
      "a mighty bellow you bring the club down before "+
      "you pounding it into the ground with a tremendous "+
      "feeling of power and satisfaction.\n");
   say(QCTNAME(TP) + " suddenly lifts the club up high and "+
      "proceeds to pound it down into the ground with "+
      "powerful strokes!\n");
   TP->command("scream");
   TP->command("shout Death to all hobbits!!");
   return 1;
}


fortify()
   {
   if(!query_wielded(TO))
      {
      write("The presence from within the club begs you to wield it.\n");
      return 1;
   }
   write("You feel power flow from within the club to fortify you against any "+
      "opponent.\n");
   say(QCTNAME(TP) + " grasps the pommel of the petrified club closely "+
      "and studies it with intensity. " + TP->query_pronoun() + " gains "+
      "an aura of fortification against all opponents.\n");
   TP->command("smile confid");
   return 1;
}

command(s)
{
   if(!query_wielded(TO))
      {
      write("You must wield the club first.\n");
      return 1;
   }
   NF(query_verb() + " what?\n");
   if(!s)
      return 0;
   if(query_verb() == "command")
      {
      if(s != "aamrfgk")
         return 0;
   }
   else
      if(s != "aamrfgk")
      return 0;
   NF("You call upon the power of the enchanted club, but "+
      "nothing happens.\n");
   if(uses < 1)
      return 0;
   write("You call upon the power of the petrified club.\n");
   write("The power of the petrified club flows into you!\n");
   write("You feel healthier.\n");
  say(QCTNAME(TP) + " prays to the demons within the club "+
      "to grant the power of it's creators.\n");
  say(QCTNAME(TP) + " suddenly seems healthier!\n");

   uses = uses > 1;

   remove_wounds();
   return 1;
}

remove_wounds()
{
   TP->heal_hp(800);
}

