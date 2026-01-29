// recletter.c - code inherited into an npc who receives a letter
//               in the postmaster tour
//
// Zima   June 13, 98
//
string* react = ({"worry","snicker","laugh","sigh","ponder","giggle",
                  "frown","gasp","nod","hmm","blink","smile"});
int     my_letternum=-1; // should be set in cloning npc
                         // see ashalagh/obj/mailsack for values & addresses
 
//
// respond_letter - the npc was given a quest letter, respond to this
//
void respond_letter(object letter, object tp)
{
   object sack   = present("_ashlagh_mailsack",tp);
   string lshort = (letter->short());
   string tpname = lower_case(tp->query_name());
 
   command("emote studies the "+lshort+" carefully.");
   if (!objectp(sack))
      {
      command("emote looks around suspiciously.");
      command("say You don't have a mailsack. You can't be the deliverer!");
      command("say I don't trust you, this might be evil magic!");
      if (!command("give letter to "+tpname))
           command("drop letter");
      return;
      }
   if ((letter->query_letternum()) != my_letternum)
      {
      command("say This is not addressed to me. You have the wrong person.");
      if (!command("give letter to "+tpname))
           command("drop letter");
      return;
      }
 
   command("emote opens the letter and reads it quickly.");
   command(react[(random(sizeof(react)))]);
   command("say Thank you for delivering this to me.");
   command("shake "+tpname);
   letter->remove_object();
   sack->set_delivered(my_letternum);
}
 
//
// check_letter
//    args:
//       ob - an object given to this npc
//       tp - origin of the object given
//    returns:
//       0  - this object wasn't a quest letter and I did nothing with it.
//       1  - this object was a quest letter and I responded appropriately.
//    function:
//       This function is invoked in enter_inv() by any npc which is to
//       receive a letter in the Postmaster Tour in Baile Ashlagh.
//       If the given object is a quest letter from a player, invokes
//       respond_letter() via set_alarm and returns 1.
//       If not, does nothing and returns 0.
 
int check_letter(object ob, object tp)
{
   if ((ob->id("_baile_ashlagh_letter")) && interactive(tp))
      {
      set_alarm(2.0,0.0,&respond_letter(ob,tp));
      return 1;
      }
   return 0;
}
 
//
// give_back - give an object back to an interactive
//
void give_back(object ob, object tp)
{
   string obs = lower_case(ob->query_name());
   command("say I can't accept this from you.");
   if (!command("give "+obs+" to "+lower_case(tp->query_name())))
        command("drop "+obs);
}
 
//
// check_letter_return - npc's enter_inv() can invoke this if it wants
//                       any non-letter object to be blindly returned
//
void check_letter_return(object ob, object tp)
{
   if (check_letter(ob,tp)) return;
   if (interactive(tp))
      set_alarm(2.0,0.0,&give_back(ob,tp));
}
