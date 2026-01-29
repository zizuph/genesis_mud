#include <stdproperties.h>
#include <macros.h>

#include "defs.h"

inherit "/d/Shire/common/lib/outroom";

create_outroom()
{
    add_prop(OBJ_I_CONTAIN_WATER, 1);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);
    TO->create_lakeroom();

    add_item(({"lake","water"}), "@@examine_lake@@\n");
    add_item("beach", "@@examine_beach@@\n");
    add_item(({"odour","reek","moss","smell","fish","fishes","bird","birds",
	       "evil","death"}),"@@examine_extra@@\n");

    add_call("enter", "[into] [in] [the] 'lake' / 'water'", "enter_water");
    add_call("swim", "[into] [in] [the] 'lake' / 'water'", "enter_water");
    add_call("dive", "[into] [in] [the] 'lake' / 'water'", "enter_water");
    add_call("jump", "[into] [in] [the] 'lake' / 'water'", "enter_water");
}

reset_outroom()
{
    TO->reset_lakeroom();
}

string
examine_lake() 
{
    switch(random(4))
    {
    case 0: return "The water is black, and judging from its odour, \n"+
                   "you would not take a dive into it.";
    case 1: return "The Sirannon Lake has a foul smell, as if it is \n"+
                   "hiding something evil deep down in its dark waters.";
    case 2: return "Yikes, the smell reeking from the lake indicates \n"+
                   "that this is *not* the place to have a bath.";
    case 3: return "Hey! Surely you could see something moving out there! \n"+
                   "An uneasy feeling creeps under your skin as you realize \n"+
		   "that something large, perhaps even super large, dwells deep \n"+
		   "down in the dark places of the Sirannon Lake.";
    }
}

string
examine_beach() 
{
    string name;
    int	   i, seed = 0;

    name = file_name(this_object());
    for(i=0;i<strlen(name);i++)
	seed += name[i];
  
    switch(random(4, seed))
    {
    case 0:
      return "There is an itching odour from the beach of the Sirannon Lake here.";
    case 1:
      return "You almost puke when seeing dead fishes and birds rotting on the beach.";
    case 2:
      return "A slimy green hideous moss lies upon the beach here.";
    case 3:
      return "A reek of death lies upon this beach. There are no signs of life.";
    }
}

string 
examine_extra()
{
  switch(random(3)) {
  case 0: return "Alas, this place has been wrecked by evil forces.\n"+
                 "This place, once being fair and overwhealming,\n"+
		 "is now but a place for creeps and terrors. There is\n"+
		 "Evil here working. Foul and perilious...";    
  case 1: return "This surely is a foul place.\n"+
                 "Death and illness.\n"+
                 "Plague and madness.\n"+
                 "The doom of Evil penetrates this area.";
  case 2: return "You start to wonder what omnious evil lies down in the waters.\n"+
                 "Surely it must be something lurking in the lake, but what?\n"+
		 "Let's hope you will never find out.";
  }
}

int
enter_water()
{
    write(break_string(
	     "You could " + query_verb() + " into the water, but you just "
	   + "cannot bear the fright of what may be lurking down there.. "
	   + "You decide not to " + query_verb() + " this water.\n", 74));
    say(QCTNAME(TP)+" looks as if "+HE_SHE(TP)+" wants to " + query_verb()
	 + "\ninto the water, but "+HE_SHE(TP)+" somehow hesitates, \n"
	 + "and decides not to dare.\n");

    return 1;
}
