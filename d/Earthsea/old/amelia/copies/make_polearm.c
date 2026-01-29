#pragma save_binary

/* Code to make polearms. Included into Bubba the blacksmith's code in
 * Gelan.
 * Code by Maniac, 26.6.95
 */

/* Action:
   Taking an order for a polearm .
*/
int
do_polearm_order(string str)
{
   object tp;
   string p, m, l, d;

   tp = this_player();

   if (!str)
       str = "";

   tell_room(environment(this_object()), QCTNAME(tp) + " places an order " +
             "for a polearm.\n", tp);
   tp->catch_msg("You place an order for a polearm.\n");

   if (objectp(query_attack())) { 
        command("rolleyes"); 
        return 1;
   } 

   if (state != AWAITING_CUSTOMER) {
       this_object()->say_busy(tp);
       return 1;
   }

   if (!parse_command(str, this_object(), "%w %w %w %w", p, m, l, d)) {
       command("say I did not understand your order, " + 
               query_npc_address_name(tp, "") + ", you should give the " +
               "weapon name, metal, length and decoration type."); 
       return 1;
   }

   if (!polearm_name_descs[p])  { 
       command("say I don't make any polearm called " + LANG_ADDART(p) + 
               ", " + query_npc_address_name(tp, "") + "."); 
       return 1;
   }

   if (!polearm_metal_descs[m]) {
       command("say I don't use any metal called " + m + " for making " +
               "polearms, " + query_npc_address_name(tp, "") + "."); 
       return 1;
   }

   if (!polearm_length_descs[l]) {
       command("say I don't make polearms of " + l + " length, " +
               query_npc_address_name(tp, "") + "."); 
       return 1;
   }

   if (!polearm_decor_descs[d]) {
       command("say I don't make polearms with " + d + " decoration, " +
               query_npc_address_name(tp, "") + "."); 
       return 1;
   }

   state = POLEARM_MAKING;
   stage = CONFIRMATION;

   customer = tp->query_real_name();
   working_on =  LANG_ADDART(d + " " + m + " " + p);
   price = (POLEARM_GREED * query_made_polearm_value(m, l)) / 100;
   polearm_order = ({p, m, l, d});

   command("say Ok, " + working_on + " will cost you " + price +
           " copper, " + query_npc_address_name(tp, "") + ".");
   command("say Please either confirm by <pay>ing, or <cancel>.");
   confirmation_alarm = set_alarm(30.0, 0.0, "end_waiting");
   return 1;
}


/* Make polearm object ready for later */
void
make_the_polearm(string p, string m, string l, string d)
{
  finished_item = clone_object(GELAN_WEAPONS + "rawpolearm");
  finished_item->set_polearm_name(p);
  finished_item->set_metal(m);
  finished_item->set_length(l);
  finished_item->set_decor_type(d);
  finished_item->make_the_polearm();
}


/* Working: on a polearm */
void
working_polearm(int ws)
{
    if (sizeof(polearm_order)) {
        switch (ws) {
            case 1: {
                command("emote puts pieces of " + polearm_order[1] + 
                        " into some " + polearm_order[0] +  
                        " blade and haft moulds."); 
                break;
            }
            case 2: {
                command("emote places some moulds containing " + 
                    polearm_order[1] +
                    " into the forge with a large pair of pliers."); 
                break;
            }
            case 3: {
                command("emote removes moulds containing molten " + 
                        polearm_order[1] + " from the forge with " +
                        "a large pair of pliers.");
                break;
            }
            case 4: {
                command("emote dips moulds containing molten " + 
                        polearm_order[1] + " into some water " +
                        "to cool them. There is a mighty hiss and a " +
                        "cloud of steam rises up.");
                break;
            }
            case 5: {
                command("emote removes the somewhat coarse " + 
                        polearm_order[1] + " " + 
                        polearm_order[0]+"-parts" + 
                        " from the moulds."); 
                       
                break;
            }
            case 6: {
                command("emote does some careful joining work on the " + 
                         polearm_order[0] + ", so that it now resembles " +
                         "a complete weapon.");
                break;
            }
            case 7: {
                command("emote does some engraving and decoration on " +
                       "the haft of the " + polearm_order[1] +  
                        " " + polearm_order[0] + ", and some blade " +
                        "sharpening.");
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
        set_alarmv(4.0, 0.0, "working_polearm", ({ws+1}));
        return;
    }
    else {
        command("confused");
        end_waiting();
        return;
    }
}
