#include "defs.h"

void remove(object ob);

CONSTRUCT_ROOM {
    set_short("The western end of a long room.");
    set_long("The western end of a long room. Here someone has scratched "+
	     "some words in the black language of Mordor. There is a narrow "+
	     "opening over some blocks of stone to the south.\n");
    add_item(({"words","scratches"}),"Perhaps read them?");
    add_item(({"blocks","stone"}),"They can be traversed, just go south.");
    add_item(({"opening","openings","exits"}),"It is all in the text, pal!");
    EXIT("litt","west");
    EXIT("longr2","east");
    EXIT("pyramid","south");
}

init() {
    ::init();
      add_action("utter","utter");
      add_action("my_read","read");
}

string
query_text()
{
    return
	"They should not be uttered aloud, but they say:\n"+
	"         Ash Nazg durbatuluk,\n"+
	"         ash Nazg gimbatul,\n"+
	"         ash Nazg thrakatuluk\n"+
	"         agh burzum-ishi krimpatul.\n";
}

my_read(str) {
  if (!str) {
    notify_fail("Read what?\n");
    return 0;
  }
  if (str == "words" || str == "scratches") {
    write(query_text());
    return 1;
  }
}
	  
utter(str) {
    if (str=="words" || str=="scratches" ||
       str == "words aloud" || str== "scratches aloud")
    {
	string *lines = explode(query_text(),"\n");
	int i;
	for(i=1;i<sizeof(lines);i++) {
	    TP->catch_msg("You hiss:"+lines[i]+"\n");
	    tell_room(TO, QCTNAME(TP)+" hisses:"+lines[i]+"\n", TP);
	}
    set_alarm(5.0, 0.0, &remove(TP));
	return 1;
    }
}

remove(whose) {
    tell_room(TO, "A dark mist forms in front of you.\n");
    tell_room(TO, "It surrounds you, penetrates you, oh my God, what's "+
		  "happening!!\n");
    if (steal(whose))
	tell_object(whose,"He steals your soul!\nThe mist evaporates.\n");
    else
	tell_object(whose,"He fills your soul with hatred and sorrow.\n");
    return 1;
}
	    
steal(whose) {
  return 0;
}
