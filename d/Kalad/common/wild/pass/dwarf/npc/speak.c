public int
e_dsay(string arg)
{
   if (!strlen(arg))
      {
      NF("Say what in the Dewar jargon?\n");
      return 0;
   }
   
   if(TP->query_skill(SS_LANGUAGE) < 10)
      {
      NF("You haven't learned the rough language used by the dewars "+
         "well enough yet.\n");
      return 0;
   }
   
   if (this_player()->query_get_echo())
      write("In the dewar jargon, you utter: " + arg + "\n");
   else
      write("Ok.\n");
   
   filter(all_inventory(environment(this_player())) - ({ this_player() }),
      "do_say", this_object(), arg);
   return 1;
}

public int
do_say(object who, string arg)
{
   int i;
   string text;
   string dummy;
   if (!living(who))
      return 0;
   if ((IS_MEMBER(who) && who->query_skill(SS_LANGUAGE) > 9) ||
         who->query_skill(SS_LANGUAGE) > 59)
   {
      tell_object(who, this_player()->query_The_name(who) + " growls " +
         "in the local dwarven jargon: " + arg + "\n");
      return 1;
   }
   if(who->query_skill(SS_LANGUAGE) < 20)
      {   
      tell_object(who, this_player()->query_The_name(who) + " growls " +
         "some harsh sounds. You find it utterly unconprehensable.\n");
      return 1;
   }
   
   /* remove vocals from arg according to ss_language skill */
   
   text="";
   for (i=0;i<strlen(arg);i++)
   {
      dummy=extract(arg,i,i);
      if(dummy != "a" && dummy !="e" && dummy != "i" &&
            dummy != "o" && dummy != "u" && dummy !="s" && dummy != "y")
      text=text+dummy;
      else
         {
         if (random(who->query_skill(SS_LANGUAGE)-20)>20)
            text=text+dummy;
         else
         switch(random(4))
         {
            case 0: text=text+"x"; break;
            case 1: text=text+"r"; break;
            case 2: text=text+"gh"; break;
            case 3: text=text+"z"; break;
            default: text=text+"r"; break;
         }
        }
   }
   tell_object(who, this_player()->query_The_name(who) + " growls "+
      "something in the local dwarven jargon. You manage to catch this: "+
      text+".\n");
}

/* kick-emote. Shall work on corpses too, and will do
* damage (small) if on living. If a hit, then combat is
   * initiated.
*/

public int
e_dkick(string arg)
{
    object *oblist, *oblive, *obdead;
   int result;
   object ob, *obj;
   mixed *hitresult;
   string str;
   string how;
   string what;
   string *name;
   int i;
   
   
   if (!strlen(arg))
      {
      allbb(" kicks the ground hard, in pure rage!.");
      write("You kick the ground hard in pure rage!\n");
      return 1;
   }
   if(arg=="all")
      {
   write("You kick at everything in sight, making a havvock!\n");
   tell_room(E(TO),QCTNAME(TP)+" kicks at everything in sight, "+
      "looking utterly mad!\n",TP);
      return 1;
   }

   NF("But you are already preparing a kick!\n");
   if(kicking) return 0;
   NF("Dkick at whom/what?\n");
   
   /* The player kicks someone, so we will make an attempt to
   * do damage and then initiate combat.
   */
   
   oblist = parse_this(arg, "[at] / [to] / [toward] [the] %l");
   if (sizeof(oblist))
      {
      set_alarm(0.0,0.0,"do_kick",oblist[0]);
      return 1;
   }
   
   
   /* The player kicks at something. This can be weapons, armours or
   * corpses. We test the first object to find out. 
   */
   
   if(!parse_command(arg,all_inventory(E(TP)), "[at] / [to] / [toward] [the] %s",what))
      return 0;
   if(!sizeof(obdead=FIND_STR_IN_OBJECT(what,E(TP))))
      return 0;
   if(sizeof(obdead)>1)
   {
      NF("Be more specific, please.\n");
      return 0;
   }
   
   if((function_exists("create_object", obdead[0]) == "/std/weapon") ||
      (function_exists("create_object", obdead[0]) == "/std/armour"))
      {
      result = ((TP->query_base_stat(SS_STR)/2)-
         (obdead[0]->query_prop(OBJ_I_WEIGHT)/1000)+15);
      if(result<0)
      {
         str="but it is so heavy that it doesn't move an inch!";
         write("Your toes really hurts from the impact, but being a dewar "+
            "you manage to make your face of pain look like a grin of "+
          "extreme cruelty. It doesn't move an inch!\n");
      }
      if(result>-1 && result<6) str="with the result that it moves an inch.";
      if(result>5 && result<21) str="making it turn around twize.";
      if(result>20 && result<41) str="making it roll around on the ground.";
      if(result>40 && result<61) str="making it almost shatter upon the impact.";
      if(result>60 && result<81) str="and watches it whirl away.";
      if(result>80) str="and sends it flying!";
      if(obdead[0]->query_prop(OBJ_I_BROKEN))
         str="just to make sure it stays broken.";
      if(result >= 0)
         write("You kick hard into the "+obdead[0]->query_short()+
            " in pure rage, "+str+"\n");
      tell_room(E(TO),QCTNAME(TP)+" kicks hard into the "+obdead[0]->query_short()+
         " on the ground in pure rage, "+str+"\n", TP);
      
      /* This treatment of the weapon/armour will damage it. */
      if (result>100) result = 100;
   if(obdead[0]->query_prop(OBJ_I_IS_MAGIC_ARMOUR) ||
     obdead[0]->query_prop(OBJ_I_IS_MAGIC_WEAPON))
      result=result/2;
   if(!obdead[0]->query_prop(OBJ_I_BROKEN))
   {
      obdead[0]->set_dull(obdead[0]->query_dull()+(result/10));
      set_alarm(1.0,0.0,"check_broken",obdead[0]);
   }
   return 1;
   }
   
   /* kicking a corpse? */
   
   if(obdead[0]->query_name()=="corpse")
      {
      name=obdead[0]->query_names();
     write("You kick hard into the "+name[5]+
         " in pure comtempt! You can hear the dry sound of ribs "+
         "cracking from the impact.\n");
      tell_room(E(TP),QCTNAME(TP)+" kicks hard into the "+name[5]+
         " in pure contempt. You can hear the dry sound of ribs "+
         "cracking from the impact.\n",TP);
      return 1;
   }
   return 0;
}

void
check_broken(object ob)
{
  if(ob->query_prop(OBJ_I_BROKEN))
   {
      tell_room(E(ob),"The "+ob->query_short()+
         " breaks!\n");
      TP->command("cackle insanely");
   }
}


void
do_kick(object who)
{
   if (!F_DARE_ATTACK(TP, who))
   {
      write("You don't dare to do it!\n");
      return;
   }
   if(!member_array(who,TP->query_enemy(-1)))
   {
      write("You can't kick that gully person now. You two are in "+
      "a deadly fight!\n");
      return;
   }
   if (who && environment(TP) != environment(who))
   {
      write("Dissapointedly, you realise that "+QTNAME(who)+" is "+
         "not here anymore.\n");
      return;
   }
   kicking=1;
   write("With delight, you prepare break some bones.\n");
   TP->attack_object(who);
   TP->add_attack_delay(2);
   TP->add_prop(LIVE_O_SPELL_ATTACK, this_object());
   return;
}


void
tell_watcher(string str, object me, object enemy)
{
   object *ob;
   int i;
   ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
   ob -= ({ enemy });
   for (i=0;i<sizeof(ob);i++)
   if (ob[i]->query_see_blood())
      ob[i]->catch_msg(str);
}


void
spell_attack(object attacker, object target)
{
   string how;
   mixed *hitresult;
   object is_here;
   
   is_here=present(target,E(attacker));
   if(!is_here)
   {
      kicking = 0;
      attacker->catch_msg("Dissapointedly, you realise that "+QTNAME(target)+
         "has dissapeared.\n");
      return;
   }
   hitresult = target->hit_me(200, W_BLUDGEON, attacker, -1);
   how = "unharmed";
   if (hitresult[0] > 0)
      how = "a rib";
   if (hitresult[0] > 5)
      how = "two ribs";
   if (hitresult[0] > 10)
      how = "some ribs";
   if (hitresult[0] > 20)
      how = "several ribs";
   if (hitresult[0] > 50)
      how = "the chest itself";
   
   if(hitresult[0] > 0)
      {
      attacker->catch_msg("The kick lands hard into "+
         QTNAME(target)+"'s chest. You hear "+
         "the dry sound of "+how+" cracking from the impact!\n");
      target->catch_msg(QCTNAME(attacker) +
         " kicks you in the chest with all "+attacker->query_possessive()+
         " might. You feel "+how+" crack from the impact!\n");
      tell_watcher(QCTNAME(attacker) + " kicks " + QTNAME(target) +
         " hard in the chest. You can hear the dry sound of "+
         how+" cracking from he impact!\n", attacker, target);
      if (target->query_hp() <= 0)
         target->do_die(attacker);
      kicking = 0;
      return;
   }
   attacker->catch_msg("You miss with the kick against "+
      QTNAME(target)+"'s chest and fall flatfaced down on the ground.\n");
   target->catch_msg(QCTNAME(attacker) +
      " tries to kick you in your chest, but misses utterly and "+
      " falls flatfaced down on the ground.\n");
   tell_watcher(QCTNAME(attacker) + " tries to kick " + QTNAME(target) +
      " in the chest, but misses utterly and falls flatfaced down "+
      " on the ground.\n", attacker, target);
   TP->add_attack_delay(2);
   kicking = 0;
   return;
}



