#pragma save_binary

/* Code to make armour. Included into Bubba the blacksmith's code in
 * Gelan.
 * Code adapted and modified from code in Gondor by Maniac, 7.94
 * Separated and given overhaul, Maniac, 7/6/95
 * Making of magical shield for polymorph quest added, Maniac, 7/9/95
 */


/* Action:
   Taking an order for some armour.
*/
int
do_armour_order(string str)
{
   object tp, jewel, brew;
   string a, m, c;

   tp = this_player();

   if (!str)
       str = "";

   tell_room(environment(this_object()), QCTNAME(tp) + " places an order " +
             "for some armour.\n", tp);
   tp->catch_msg("You place an order for some armour.\n");

   if (objectp(query_attack())) { 
        command("rolleyes");  
        return 1;
   } 

   if (state != AWAITING_CUSTOMER) {
       this_object()->say_busy(tp);
       return 1;
   }

   /* Player can order magical shield, part of polymorph quest */
   if (str == "magical shield") {
       if (tp->test_bit(PQ_DOM, PQ_GROUP, PQ_BIT)) {
            command("ponder wasting one's time.");
            return 1;
       }

       if (present(SHIELD_NAME, tp)) {
           command("say You've got a magical shield already, why do " +
                   "you want another one?");
           return 1;
       }

       if (tp->query_prop(LIVE_I_FOUGHT_CALIA_PQ_DEMON)) {
           jewel = present(JEWEL_NAME, tp);
           brew = present(BREW_NAME, tp);
           if (!objectp(jewel) || !objectp(brew))  {
               command("say I'd like to help you, but I don't think you " +
                       "have the necessary items for me to make one.");
               return 1;
           }
           else {
               price = (tp->query_average_stat() * 30);
               command("say I can make you the type of magical shield " +
                       "that you require for " + price + " copper.");
               command("say Please either confirm by <pay>ing, or <cancel>.");

               state = ARMOUR_MAKING;
               stage = CONFIRMATION;

               customer = tp->query_real_name();
               working_on = "a magical shield";

               armour_order = ({"shield", "steel", "magical"});
               confirmation_alarm = set_alarm(30.0, 0.0, "end_waiting");
               return 1;
            }
        }
    }


   if (!parse_command(str, this_object(), "%w %w %w", a, m, c)) {
       command("say I did not understand your order, " + 
               query_npc_address_name(tp, "") + ", you should give the " +
               "armour type, metal and construction."); 
       return 1;
   }

   if (!armour_type_at[a])  { 
       command("say I don't make an armour type called " + a + ", " +
               query_npc_address_name(tp, "") + "."); 
       return 1;
   }

   if (!armour_metal_weight_mult[m]) {
       command("say I don't have any metal called " + m + ", " +
               query_npc_address_name(tp, "") + "."); 
       return 1;
   }

   if (((a == "body-armour") || (a == "greaves") || (a == "bracers")) && 
       (!armour_const_rating[c])) {
       command("say I don't make a construction type " + c + " for " +
               a + ", " + query_npc_address_name(tp, "") + "."); 
       return 1;
   }

   if ((a == "shield") && (!shield_const_rating[c])) {
       command("say I don't make a construction type " + c + " for " +
               "shields, " + query_npc_address_name(tp, "") + "."); 
       return 1;
   }

   if ((a == "helm") && (!helm_const_rating[c])) {
       command("say I don't make a construction type " + c + " for " +
               "helms, " + query_npc_address_name(tp, "") + "."); 
       return 1;
   }

   state = ARMOUR_MAKING;
   stage = CONFIRMATION;

   customer = tp->query_real_name();
   if ((a == "bracers") || (a == "greaves"))
       working_on = "a pair of " +  m + " " + c + " " + a;
   else 
       working_on = LANG_ADDART(m + " " + c + " " + a);

   price = (ARMOUR_GREED * query_made_armour_value(a, m, c)) / 100;
   armour_order = ({a, m, c});

   command("say Ok, " + working_on + " will cost you " + price +
           " copper, " + query_npc_address_name(tp, "") + ".");
   command("say Please either confirm by <pay>ing, or <cancel>.");
   confirmation_alarm = set_alarm(30.0, 0.0, "end_waiting");
   return 1;
}


/* Make armour object ready for later */
void
make_the_armour(string a, string m, string c)
{
  /* Check to see if it's the magical shield for the polymorph quest */
  if ((a == "shield") && (m == "steel") && (c == "magical")) {
      finished_item = clone_object(PQ_SHIELD);
      return;
  }

  finished_item = clone_object(GELAN_ARMOURS + "rawarmour");
  finished_item->set_armtype(a);
  finished_item->set_metal(m);
  finished_item->set_const(c);
  finished_item->make_the_armour();
}


/* Working: on armour */
void
working_armour(int ws)
{
    if (sizeof(armour_order)) {
        switch (ws) {
            case 1: {
                command("emote puts pieces of " + armour_order[1] + 
                        " into some " + armour_order[0]+"-part-" +
                        "shaped moulds."); 
                break;
            }
            case 2: {
                if (armour_order[2] == "magical")
                    command("emote carefully pours the strange brew " +
                            "into the moulds.");
                command("emote places some moulds containing " + 
                    armour_order[1] +
                    " into the forge with a large pair of pliers."); 
                break;
            }
            case 3: {
                command("emote removes moulds containing molten " + 
                        armour_order[1] + " from the forge with " +
                        "a large pair of pliers.");
                if (armour_order[2] == "magical") 
                    tell_room(environment(this_object()), "The " +
                        armour_order[1] + 
                        " seems to have a strange colour and aura to it.\n");
                break;
            }
            case 4: {
                command("emote dips moulds containing molten " + 
                        armour_order[1] + " into some water " +
                        "to cool them. There is a mighty hiss and a " +
                        "cloud of steam rises up.");
                if (armour_order[2] == "magical") 
                    tell_room(environment(this_object()), "The steam " +
                        "sparkles with magic!\n");
                break;
            }
            case 5: {
                command("emote removes the somewhat coarse " + 
                        armour_order[1] + " " + armour_order[0]+"-parts" + 
                        " from the moulds."); 
                break;
            }
            case 6: {
                command("emote does some joining work and adds some " + 
                        "strapping to the " + armour_order[0] + ".");
                break;
            }
            case 7: {
                command("emote does some finishing work and " +
                        "engraving on the " + armour_order[1] +  
                        " " + armour_order[0] + ".");
                if (armour_order[2] == "magical")
                    command("emote then carefully sets the sapphire at " +
                            "the centre of the shield.");
                break;
           }
            case 8: {
                finish_work();
                return;
                break;
            }
            default: {
                command("confused");
                end_waiting();
                return;
                break;
            }
        }
        set_alarmv(4.0, 0.0, "working_armour", ({ws+1}));
        return;
    }
    else {
        command("confused");
        end_waiting();
        return;
    }
}
