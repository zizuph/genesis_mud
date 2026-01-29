/*
 * Removed defans from this file
 * Tapakah, 07/2021
 */

#pragma no_clone

#include <macros.h>
#include "defs.h"
//
// return flask to player or drop it.
//
void
do_return_flask (string fshort, object tp, object rm)
{
  if (present(tp,rm))
    command("give flask to "+(lower_case(tp->query_name())));
  command("drop flask");
}
 
//
// do_bless_oil - do a step in the process of blessing the oil
//
void
do_bless_oil (object flask, object tp, int step)
{
  string fshort=(flask->query_short());
  object rm=ENV(TO);
  
  switch(step) {
  case 1:
    if (!present(tp,rm))
      return;
    if (!present(flask,tp))
      return;
    tp->catch_msg(QCTNAME(TO)+" takes the "+fshort+" from you.\n");
    tell_room(rm,QCTNAME(TO)+ " takes "+LANG_ART(fshort)+" "+fshort+
              " from "+QTNAME(tp)+".\n",tp);
    flask->move(TO);
    break;
  case 2:
    if (!present(flask,TO))
      return;
    if ((flask->query_amt() <= 0) || (flask->query_blessed())) {
      command("emote looks at the "+fshort+" preponderously.");
      do_return_flask(fshort,tp,rm);
      return;
    }
    command("emote raises the flask above his head with his left hand.");
    command("emote places his right hand on the flask and begins to "+
            "focus on it.");
    break;
  case 3:
    if (!present(flask,TO))
      return;
    command("emote chants: Bannaghey Ardargh eh shoh dorum pard tum!");
    tell_room(rm,"The flask glows briefly.\n");
    flask->set_blessed();
    break;
  case 4:
    if (!present(flask,TO))
      return;
    command("emote lowers the flask slowly and smiles mysteriously.");
    break;
  default: //and case 5
    do_return_flask(fshort,tp,rm);
    return;
  }
  set_alarm(5.0,0.0,&do_bless_oil(flask,tp,(step+1)));
}
 
//
// ask_bless_oil - should be a vbfc in add_ask to bless oil, returns cmd
//
string
ask_bless_oil () {
  object flask=present(SR_FLASK,TP);
  if (!objectp(flask))
    return ("emote looks at you strangely.");
  else {
    set_alarm(5.0,0.0,&do_bless_oil(flask,TP,1));
    return ("emote smiles and nods favourably toward you.");
  }
}
