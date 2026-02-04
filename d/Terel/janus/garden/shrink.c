/* shrink.c */
/* janus 920901 
 */

inherit "/std/room";
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#define TP             this_player()
#define TO             this_object()

#define LIVE_S_FROM_FILE "_live_s_from_file"

public void
init()
{
  ::init();
}

public void
reset_room()
{
  int ii;
  object monster, krympp;
  
  if (!present("krympp")) {;
    krympp=clone_object("/d/Terel/janus/other/krympp");
    krympp->move(this_object());
  }
  ii=random(8);
  if (ii == 0) {
    if (present("rat")) return;
    monster=clone_object("/d/Terel/janus/monsters/rat");
    monster->move_living("M", this_object());
  } else if (ii == 1) {
    if (present("wbug")) return;
    monster=clone_object("/d/Terel/janus/monsters/wwbug");
    monster->move_living("M", this_object());
  } else if (ii == 2) {
    if (present("roach")) return;
    monster=clone_object("/d/Terel/janus/monsters/roach");
    monster->move_living("M", this_object());
  } else if (ii == 3) {
    if (present("spider")) return;
    monster=clone_object("/d/Terel/janus/monsters/spider");
    monster->move_living("M", this_object());
  }  
  
}

public void
create_room()
{
  set_short("somewhere");
  set_long("You must have shrunk to a miniscule size. "+
      "Everything around you is gargantuan. A boulder to your "+
      "left must be a grain of sand. Better not stay here too long or "+
      "you will end up as a wet spot under someones shoe. Hope that "+ 
      "no one will accidently step on you while you are this small.\n");
  reset_room();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (!living(ob) || !strlen(ob->query_prop(LIVE_S_FROM_FILE)))
        return;
    
    set_alarm(40.0, -1.0, "wait_and_grow", ob);
}

public void
wait_and_grow(object who)
{
    string back;
    
    if (!who) return;
    
    back = who->query_prop(LIVE_S_FROM_FILE);
    
    if (environment(who) == TO && strlen(back)) {
        who->catch_msg("You grow back to normal size.\n");
        who->remove_prop(LIVE_S_FROM_FILE);
        who->move_living("this miniature world", back, 1);
        remove_object();
    }
}
