/* A special quest draconian on the plains.
 * He'll appear only once every blue moon.
 */

inherit "/d/Krynn/solamn/splains/living/aurak";

/* when the dracs on the plains are changed to the new ones,
 * change this to inherit "/d/Krynn/std/aurak";
 */

#include "/d/Krynn/common/defs.h"

#define IDDRAC_GROUP   3
#define IDDRAC_BIT     6

void
create_aurak()
{
  ::create_aurak();

    add_ask("[about] [for] 'quest' / 'help' / 'task'","give_quest",2);
    
}


void
give_quest(object asker)
{
  string nm = asker->query_real_name();

  command("whisper to " + nm + " I need you to do something for me.");
  command(": looks at |" + nm + "| suspisiouly.");
  command("whisper to " + nm + " .");
  command("whisper to " + nm + " .");
  command("whisper to " + nm + " .");
  command("whisper to " + nm + " .");

}
