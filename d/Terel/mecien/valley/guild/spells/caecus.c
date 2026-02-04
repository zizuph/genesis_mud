#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#define EN environment
#define TP this_player()
#define TO this_object()
#define COST 100



caecus(){
object who;

if(!present("sacred_mantle", TP)) return "You will need the sacred mantle.\n";

if(TP->query_mana() < COST ) return "You do not have the strength.\n";

  tell_room(EN(TP), QCTNAME(TP) + " begins to shake and tremble as if struck by some icy wind.\n", TP);
TP->catch_msg("You sense the coming of the nether world into your body.\n");
  who = TP;
  set_alarm(7.0, 0.0, "unseen", who);
  TP->add_mana(-COST);
return 1;
}

unseen(object who){

tell_room(EN(who), "A darkness takes shape and consumes " + QTNAME(who) +
" within its folds.\n", who);
who->catch_msg("You are taken into the unseen world of the spirits.\n");
who->set_invis(1);
set_alarm(60.0, -1.0, "appear", who);
}

appear(object who){
who->set_invis(0);
who->catch_msg("The darkness of the nether world leaves you.\n");
tell_room(EN(who), "A darkness forms quickly and " + QNAME(who) +
" appears from it.\n", who);
}

