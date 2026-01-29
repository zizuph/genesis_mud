#pragma save_binary

/* Code to make staffs. Included into Bubba the blacksmith's code in
 * Gelan.
 * Code by Maniac, 26.6.95
 */

/* Action:
   Taking an request for a staff .
*/
int
do_staff_request(string str)
{
   object tp;
   string p, m, l, d;

   tp = this_player();

   if (!str)
       str = "";

   tell_room(environment(this_object()), QCTNAME(tp) + " places an request " +
             "for a staff.\n", tp);
   tp->catch_msg("You place an request for a staff.\n");

   if (state != AWAITING_CUSTOMER) {
       this_object()->say_busy(tp);
       return 1;
   }

   if (!parse_command(str, this_object(), "%w %w %w %w", p, m, l, d)) {
       command("say I did not understand your request, " + 
               query_npc_address_name(tp, "") + ", you should give the " +
               "weapon name, metal, length and decoration type."); 
       return 1;
   }

   if (!staff_name_descs[p])  { 
       command("say I don't make any staff called " + LANG_ADDART(p) + 
               ", " + query_npc_address_name(tp, "") + "."); 
       return 1;
   }

   if (!staff_metal_descs[m]) {
       command("say I don't use any metal called " + m + " for making " +
               "staffs, " + query_npc_address_name(tp, "") + "."); 
       return 1;
   }

   if (!staff_length_descs[l]) {
       command("say I don't make staffs of " + l + " length, " +
               query_npc_address_name(tp, "") + "."); 
       return 1;
   }

   if (!staff_decor_descs[d]) {
       command("say I don't make staffs with " + d + " decoration, " +
               query_npc_address_name(tp, "") + "."); 
       return 1;
   }

   state = STAFF_MAKING;
   stage = CONFIRMATION;

   customer = tp->query_real_name();
   working_on =  LANG_ADDART(d + " " + m + " " + p);
   price = (STAFF_GREED * query_made_staff_value(m, l)) / 100;
   staff_request = ({p, m, l, d});

   command("say Ok, " + working_on + " will cost you " + price +
           " copper, " + query_npc_address_name(tp, "") + ".");
   command("say Please either confirm by <pay>ing, or <cancel>.");
   confirmation_alarm = set_alarm(30.0, 0.0, "end_waiting");
   return 1;
}


/* Make staff object ready for later */
void
make_the_staff(string p, string m, string l, string d)
{
  finished_item = clone_object("rawstaff");
  finished_item->set_staff_name(p);
  finished_item->set_metal(m);
  finished_item->set_length(l);
  finished_item->set_decor_type(d);
  finished_item->make_the_staff();
}


/* Working: on a staff */
void
working_staff(int ws)
{
    if (sizeof(staff_request)) {
        switch (ws) {
            case 1: {
                command("emote puts pieces of " + staff_request[1] + 
                        " into some " + staff_request[0] +  
                        " blade and haft moulds."); 
                break;
            }
            case 2: {
                command("emote places some moulds containing " + 
                    staff_request[1] +
                    " into the forge with a large pair of pliers."); 
                break;
            }
            case 3: {
                command("emote removes moulds containing molten " + 
                        staff_request[1] + " from the forge with " +
                        "a large pair of pliers.");
                break;
            }
            case 4: {
                command("emote dips moulds containing molten " + 
                        staff_request[1] + " into some water " +
                        "to cool them. There is a mighty hiss and a " +
                        "cloud of steam rises up.");
                break;
            }
            case 5: {
                command("emote removes the somewhat coarse " + 
                        staff_request[1] + " " + 
                        staff_request[0]+"-parts" + 
                        " from the moulds."); 
                       
                break;
            }
            case 6: {
                command("emote does some careful joining work on the " + 
                         staff_request[0] + ", so that it now resembles " +
                         "a complete weapon.");
                break;
            }
            case 7: {
                command("emote does some engraving and decoration on " +
                       "the haft of the " + staff_request[1] +  
                        " " + staff_request[0] + ", and some blade " +
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
        set_alarmv(4.0, 0.0, "working_staff", ({ws+1}));
        return;
    }
    else {
        command("confused");
        end_waiting();
        return;
    }
}
