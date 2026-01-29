#pragma save_binary

/* Repair code for Theros - Arman, October 2016
 *
 * Based on code for the blacksmith Bubba in Gelan.
 * Code included into theros.c
 *
 * Code originally adapted from code from Krynn and Gondor 7/94 by Maniac
 * Modified and given overhaul 8/6/95  by Maniac
 * Mending weapons taken out 30/8/95  by Maniac
 */


/* Code for fixing of weapons starts here */


/* Calculate value for waxing a weapon */
int
calc_wax_value(object obj)
{
   if (obj->query_prop(OBJ_I_BROKEN))
      return -1;

   if (!F_LEGAL_WEAPON_REPAIR_CORR(obj->query_repair_corr()+1,
                                  obj->query_corroded()))
       return -1;

   return obj->query_repair_cost_corr();
}


/* Calculate value for sharpening a weapon */
int
calc_sharpen_value(object obj)
{
   if (obj->query_prop(OBJ_I_BROKEN))
      return -1;

   if (!F_LEGAL_WEAPON_REPAIR_DULL(obj->query_repair_dull()+1,
                                  obj->query_dull()))
       return -1;

   return obj->query_repair_cost_dull();
}


/* Wax a weapon */
void
fix_wax(object obj)
{
   obj->set_repair_corr(obj->query_repair_corr() + 1);
}


/* sharpen a weapon */
void
fix_sharpen(object obj)
{
   obj->set_repair_dull(obj->query_repair_dull() + 1);
}


/* Tell player cost for various repairs for a particular weapon */
int
do_w_cost(string str)
{
   object *weapon, tp;
   int v1, v2, v3;

   tp = this_player();

   tell_room(environment(this_object()), QCTNAME(tp) + " enquires about " + 
             "the prices for fixing " + tp->query_possessive() + " " + 
             str + ".\n", tp);
   tp->catch_msg("You enquire about the prices for fixing your " + str +  
                 ".\n");

   if (objectp(query_attack())) { 
       command("rolleyes"); 
       return 1;
   } 

   if (state != AWAITING_CUSTOMER) {
       say_busy(tp);
       return 1;
   }
                   
   if (!str || !(weapon = FIND_STR_IN_OBJECT(str,tp)) ||
       !sizeof(weapon))
   {
      command("say Which weapon, " + query_npc_address_name(tp, "") + 
                     "?");
      return 1;
   }

   if (sizeof(weapon) > 1)
   {
      command("say Be more specific, " + query_npc_address_name(tp, "") +
                  ". Which one?");
      return 1;
   }

   if (function_exists("create_object",weapon[0]) != "/std/weapon")
   {
      command("say That is not really a weapon, " + 
               query_npc_address_name(tp, "") + ".");
      return 1;
   }

   v1 = calc_sharpen_value(weapon[0]);
   v2 = calc_wax_value(weapon[0]);

   command("say Sharpening that " + weapon[0]->short() + " "
       + ((v1 == -1) ? "is not necessary. "
                     : ("would cost " + v1 + " coppers. "))
       + "Waxing it "
       + ((v2 == -1) ? "is not necessary. "
                     : ("would cost " + v2 + " coppers. ")));
   command("smile " + tp->query_name() );
   return 1;
}


/* Action : 
   Carry out fixing of a weapon (may be waxing or sharpening) 
*/
int
do_w_fix(string str)
{
   object *weapon, tp;
   int int_str, value, *money_arr;
   string item_name, pay_type, get_type, coin_pay_text, coin_get_text,
          verb;

   verb = query_verb();

   notify_fail(capitalize(verb) + " what?\n");
   if (!str)
      return 0;

   tp = this_player();

   tell_room(environment(this_object()), QCTNAME(tp) + " asks " + 
             QTNAME(this_object()) + " to " + verb + " " + 
             tp->query_possessive() + " " + str + ".\n", tp);
   tp->catch_msg("You ask " + QTNAME(this_object()) + " to " +
                 verb + " your " + str + ".\n");

   if (objectp(query_attack())) { 
       command("rolleyes"); 
       return 1;
   } 

   if (state != AWAITING_CUSTOMER) {
       say_busy(tp);
       return 1;
   }

   /*   Check if the player defines what she wants to pay with
    *   and what you would like in return.
    */
   if (sscanf(str, "%s for %s and get %s",item_name,pay_type,get_type) != 3)
   {
      get_type = "";
      /* Hmmm... Maybe she only wishes to pay with a certain type */
      if (sscanf(str, "%s for %s", item_name, pay_type) != 2)
      {
         pay_type = "";
         item_name = str;
      }
   }

   if (pay_type != "")
   {
      if (member_array(pay_type, MONEY_TYPES) < 0)
      {
         command("say I don't accept those " + pay_type + " coins, " + 
                 query_npc_address_name(tp, "") + "."); 
         return 1;
      }
   }

   if (get_type != "")
   {
      if (member_array(get_type, MONEY_TYPES) < 0)
      {
         command("say " + capitalize(get_type) + " coins? Never " +
                        "heard of those!");
         return 1;
      }
   }

   if (!(weapon = FIND_STR_IN_OBJECT(item_name,this_player())) ||
       !sizeof(weapon))
      {
         command("say " + capitalize(verb) + " what, " +
                        query_npc_address_name(tp, "") + "?");
         return 1;
      }

   if (sizeof(weapon) > 1)
     {
      command("say Be more specific, " + query_npc_address_name(tp, "") +
                     ", which one?");
      return 1;
     }

   if (function_exists("create_object",weapon[0]) != "/std/weapon")
     {
      command("say That is not really a weapon, " +
                   query_npc_address_name(tp, "") + ".");
      return 1;
     }

   value = call_other(this_object(), "calc_"+verb+"_value", weapon[0]);

   if (value == -1)
   {
      command("say I cannot " + verb + " that any further, " +
                     query_npc_address_name(tp, "") + ".");
      return 1;
   }

   /* Try to take the money */
   if (sizeof(money_arr = pay(value, tp, pay_type, 0, 0, get_type)) == 1)
   {
      if (money_arr[0] == 1)
      {
         command("say I think that " + weapon[0]->short() + 
                 " is a bit more expensive, " + 
                 query_npc_address_name(tp, "") + "."); 
         return 1;
      }
      if (money_arr[0] == 2)
      {
         command("say You do not have any " + pay_type + " coins, " +
                  query_npc_address_name(tp, "") + ".");
         return 1;
      }
      else
      {
         command("say I think that " + weapon[0]->short() + " is a " +
                 "bit too expensive for you, " + 
                 query_npc_address_name(tp, "") + ".");
         return 1;
      }
   }

   /* It is paid for, so let's fix the weapon */
   value = call_other(this_object(), "fix_"+verb, weapon[0]);

   tp->catch_msg("You give " + QTNAME(this_object()) + " the " 
                 + weapon[0]->short() + ".\n");
   say(QCTNAME(tp) + " gives " + QTNAME(this_object()) + " " + 
       tp->query_possessive() + " " + weapon[0]->short() + ".\n");

   tell_room(environment(this_object()),
        QCTNAME(this_object()) + " "+verb+((verb == "wax") ? "es" : "s")+ 
        " the " + weapon[0]->short() + ".\n"
      + QCTNAME(this_object()) + " gives the weapon back.\n");

   coin_pay_text = text(exclude_array(money_arr, sizeof(MONEY_TYPES), 
			sizeof(MONEY_TYPES)*2-1));
   coin_get_text = text(exclude_array(money_arr, 0, sizeof(MONEY_TYPES)-1));
   tp->catch_msg("You pay " + QTNAME(this_object())+" "+coin_pay_text+".\n");
  
   say(QCTNAME(tp)+" pays "+QTNAME(this_object())+" "+coin_pay_text+ 
       ".\n");

   if (coin_get_text)
     {
      tp->catch_msg("You get " + coin_get_text + " in return.\n");
      say(QCTNAME(tp) + " gets " + coin_get_text + " in return.\n");
     }

   return 1;
}


/* Code for fixing of weapons ends here */



/* Code for fixing of armours starts here */

/* Tell player cost for repairing a particular armour */
int
do_a_cost(string str)
{
   int cond, rep, times, price;
   object *armour, tp;

   tp = this_player();

   tell_room(environment(this_object()), QCTNAME(tp) + " enquires about " + 
             "the prices for fixing " + tp->query_possessive() + " " + 
             str + ".\n", tp);
   tp->catch_msg("You enquire about the prices for fixing your " + str +  
                 ".\n");

   if (objectp(query_attack())) { 
       command("rolleyes"); 
       return 1;
   } 

   if (state != AWAITING_CUSTOMER) {
       say_busy(tp);
       return 1;
   }

   if (!str || !(armour = FIND_STR_IN_OBJECT(str,tp)) ||
       !sizeof(armour))
   {
      command("say Which armour, " + query_npc_address_name(tp, "") + 
              "?");
      return 1;
   }

   if (sizeof(armour) > 1)
   {
      command("say Be more specific, " + query_npc_address_name(tp, "") +
                  ". Which one?");
      return 1;
   }

   if (!(armour[0]->check_armour()))
   {
      command("say That is not really an armour, " + 
               query_npc_address_name(tp, "") + ".");
      return 1;
   }

  /* blacksmith can't fix broken armours */
  if (armour[0]->query_prop(OBJ_I_BROKEN))
  {
    command("say That " + armour[0]->short() + " is broken, " +
            "I cannot fix it.");
    return 1;
  }

  cond = armour[0]->query_condition();
  rep = armour[0]->query_repair();
  
  if (!cond)
  {
    command("say That "+armour[0]->short()+" is in excellent condition!");
    command("say I don't need to do anything with it.");
    return 1;
  }

  times = 0;
  while (F_LEGAL_ARMOUR_REPAIR(rep + times, cond))
      times++;
  
  price = armour[0]->query_repair_cost() * times;

  if (rep) {
      command("say I notice that "+armour[0]->short()+
          " has been fixed before.");
      if (F_LEGAL_ARMOUR_REPAIR(rep+1,cond)) {
          command("say It can still be fixed though.");
          command("say It will cost " + MONEY_TEXT_SPLIT(price) +
              " to fix.");
          return 1;
      }
      command("say It has been fixed as much as possible, I can do " +
          "nothing more.");
      command("sigh");
      return 1;
  }
  
  command("say This "+armour[0]->short()+" is damaged. I can fix it " +
          "for...hmm..");
  command("say ...about "+ MONEY_TEXT_SPLIT(price) +" I guess.");
  return 1;
}



/* Action : 
   Carry out fixing of an armour until it can't be fixed further 
*/
int
do_a_fix(string str)
{
   object *armour, tp;
   int int_str, price, *money_arr, cond, rep, times;
   string item_name, pay_type, get_type, coin_pay_text, coin_get_text,
          verb;

   notify_fail("Fix what armour?\n");
   if (!str)
      return 0;

   tp = this_player();

   tell_room(environment(this_object()), QCTNAME(tp) + " asks " + 
             QTNAME(this_object()) + " to fix " + 
             tp->query_possessive() + " " + str + ".\n", tp);
   tp->catch_msg("You ask " + QTNAME(this_object()) + " to " +
                 "fix your " + str + ".\n");

   if (objectp(query_attack())) { 
       command("rolleyes"); 
       return 1;
   } 

   if (state != AWAITING_CUSTOMER) {
       say_busy(tp);
       return 1;
   }

   /*   Check if the player defines what she wants to pay with
    *   and what you would like in return.
    */
   if (sscanf(str, "%s for %s and get %s",item_name,pay_type,get_type) != 3)
   {
      get_type = "";
      /* Hmmm... Maybe she only wishes to pay with a certain type */
      if (sscanf(str, "%s for %s", item_name, pay_type) != 2)
      {
         pay_type = "";
         item_name = str;
      }
   }

   if (pay_type != "")
   {
      if (member_array(pay_type, MONEY_TYPES) < 0)
      {
         command("say I don't accept those " + pay_type + " coins, " + 
                 query_npc_address_name(tp, "") + "."); 
         return 1;
      }
   }

   if (get_type != "")
   {
      if (member_array(get_type, MONEY_TYPES) < 0)
      {
         command("say " + capitalize(get_type) + " coins? Never " +
                        "heard of those!");
         return 1;
      }
   }

   if (!(armour = FIND_STR_IN_OBJECT(item_name,this_player())) ||
       !sizeof(armour))
      {
         command("say Fix what, " +
                        query_npc_address_name(tp, "") + "?");
         return 1;
      }

   if (sizeof(armour) > 1)
     {
      command("say Be more specific, " + query_npc_address_name(tp, "") +
                     ", which one?");
      return 1;
     }

   if (!(armour[0]->check_armour()))
     {
      command("say That is not really an armour, " +
                   query_npc_address_name(tp, "") + ".");
      return 1;
     }

  /* blacksmith can't fix broken armours */
  if (armour[0]->query_prop(OBJ_I_BROKEN))
  {
    command("say That " + armour[0]->short() + " is broken, " +
            "I cannot fix it.");
    return 1;
  }
    
  cond = armour[0]->query_condition();
  rep = armour[0]->query_repair();
  
  if (!cond)
  {
    command("say That "+armour[0]->short()+" is in excellent condition!");
    command("say I don't need to do anything with it.");
    return 1;
  }

  if (rep && !(F_LEGAL_ARMOUR_REPAIR(rep+1,cond))) {
    command("say It has been fixed as much as possible, I can do " +
            "nothing more.");
    command("sigh");
    return 1;
  }

  times = 0;
  while (F_LEGAL_ARMOUR_REPAIR(rep + times, cond))
      times++;
  
  price = armour[0]->query_repair_cost() * times;
  
  /* Try to take the money */
  if (sizeof(money_arr = pay(price, tp, pay_type, 0, 0, get_type)) == 1)
  {
      if (money_arr[0] == 1)
      {
          command("say I think that the repair " +
              " will be a bit more expensive, " + 
              query_npc_address_name(tp, "") + "."); 
          return 1;
      }
      if (money_arr[0] == 2)
      {
          command("say You do not have any " + pay_type + " coins, " +
                  query_npc_address_name(tp, "") + ".");
          return 1;
      }
      else
      {
          command("say I think that the repair is " + 
              "too expensive for you, " + 
              query_npc_address_name(tp, "") + ".");
          return 1;
      }
  }
  
   coin_pay_text = text(exclude_array(money_arr, sizeof(MONEY_TYPES), 
			sizeof(MONEY_TYPES)*2-1));
   coin_get_text = text(exclude_array(money_arr, 0, sizeof(MONEY_TYPES)-1));

   tp->catch_msg("You pay " + QTNAME(this_object())+" "+coin_pay_text+".\n");
  
   say(QCTNAME(tp)+" pays "+QTNAME(this_object())+" "+coin_pay_text+ 
       ".\n");

   if (coin_get_text)
   {
      tp->catch_msg("You get " + coin_get_text + " in return.\n");
      say(QCTNAME(tp) + " gets " + coin_get_text + " in return.\n");
   }

   tp->catch_msg("You give " + QTNAME(this_object()) + " the " 
                 + armour[0]->short() + ".\n");
   say(QCTNAME(tp) + " gives " + QTNAME(this_object()) + " " + 
       tp->query_possessive() + " " + armour[0]->short() + ".\n");

   /* carry out the fixing */
   while (F_LEGAL_ARMOUR_REPAIR(rep+1,cond)) {
      armour[0]->set_repair((armour[0]->query_repair())+1);
      rep++;
   }

  if(!armour[0]->query_value())  /* broken */
  {
      command("emote tries to fix the " + armour[0]->short() + 
              " but fails.");
      command("hmm");
      command("say I'm afraid I didn't manage to fix your armour.");
      command("say Here, take it back!");
  }
  else
      command("emote fixes the " + armour[0]->short() + ".");

  command("emote gives the armour back.");

  return 1;
}

/* Code for fixing of armours ends here */
