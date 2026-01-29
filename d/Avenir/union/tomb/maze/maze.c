#pragma strict_types
#include "../defs.h"

inherit "/d/Avenir/common/map/map_room";

#include <language.h>
#include <composite.h>


public mapping opp = ([
           "up" : "down", "down" : "up",
        "north" : "south", "east" : "west",
        "south" : "north", "west" : "west",
    "northwest" : "southeast", "northeast" : "southwest",
    "southeast" : "northwest", "southwest" : "northeast",
]);

#if 1
public mapping way_out = ([
    18 : 19, 17 : 18, 16 : 8, 15 : 6, 14 : 3,
    13 :  6, 12 : 4,  11 : 4, 10 : 3,  9 : 17, 8 : 3, 7 : 2,
     6 : 2,   5 : 1,   4 : 1 , 3 : 9,  2 : 1,  1 : 3
]);
#endif

public string *words = ({ }), *wlist = WORDS;


public void
create_maze(void)
{
}

public nomask void
create_room(void)
{
    string *dirs;

    ::create_room();

    dirs = query_exit_cmds();

    foreach(string dir: dirs)
    {
	string wrd = one_of_list(wlist);
	words += ({ wrd });

	add_item(({dir +" door", dir +"ern door",
		dir +" doorway", dir +"ern doorway", dir}),
	    "Over the " + dir + "ern doorway is written the word: " +
	    CAP(wrd) + ".\n");

	add_cmd_item(({dir +" door", dir +"ern door",
		dir +" doorway", dir +"ern doorway",
		dir +" word", dir +"ern word", dir}),
	    "read", "The word carved over the " + dir +
	    "ern doorway reads: "+ CAP(wrd) + ".\n");
     }

    set_short("bare room");
    set_long("Grey walls of soft sandstone make this room bare and "+
	"strange. @@exits_desc@@ "+ ((sizeof(dirs) > 1) ?
	    "Over each of the doorways a single word is carved into "+
	    "the stone." : "Over the doorway a single word is carved "+
	    "into the stone.") + "\n");

    add_item(({"door","doors","doorway","doorways"}),
	"There "+ (sizeof(dirs) > 1 ?
	    "are "+ LANG_WNUM(sizeof(dirs)) +" doorways" :
	    "is one doorway") +" leading from the room to the "+
	COMPOSITE_WORDS(dirs) + ".\n");

    add_item(({"word","words"}),
	"Examine the word over which doorway?\n");

    add_cmd_item(({"door","doorway","word","words"}),
	"read", "Read the word over which doorway?\n");

    set_noshow_obvious(1);
    create_maze();
}

public string *messages = ({
    "You can hear footsteps in the distance.\n",
    "Soft, eerie music can be heard from down the passages.\n",
    "Your footsteps pad lightly along the sandstone floor.\n",
    "Shadows flicker along the walls, making web-like patterns.\n",
    "A feeling of despair falls over you.\n",
    "You hear the distant sound of singing.\n"
});

public int
add_word(string exit)
{
    int which = member_array(exit, query_exit_cmds());

    if (!present(TP))
        return 1;

    if (which == -1 || which >= sizeof(words))
	return 0;

    /* Red herring messages */
    if (!random(20))
        write(one_of_list(messages));

    write("You pass along a narrow, twisty passage, and come out into "+
	"a similar room.\n");

    if (!strlen(words[which]))
	return 0;

    /* Add the word prop to the player */
    TP->add_prop(WORD_PROP, TP->query_prop(WORD_PROP) ?
	TP->query_prop(WORD_PROP) +" "+ words[which] : words[which]);
}

public varargs int
add_exit(string place, string cmd, mixed efunc, mixed tired, mixed non_obv)
{
    return ::add_exit(place, cmd, &add_word(cmd), tired, non_obv);
}

public string
exits_desc(void)
{
    string *dirs = query_exit_cmds();

    switch(sizeof(dirs))
    {
      case 0:
         return "There is no way out.";
      case 1:
         return "There is one doorway, to the "+ opp[dirs[0]] +".";
      case 2:
         return (dirs[0] == opp[dirs[1]]) ?
	     "Doorways on opposite ends of the room open up to the "+
	     dirs[1] +" and the "+ dirs[0] +"." :
	     "There are two doorways at the "+ dirs[0] +" and "+ dirs[1] +
	     " sides of the room.";
      case 3:
         return "Three doorways lead out to the "+
	     COMPOSITE_WORDS(dirs) + ".";
      default:
         return "There are "+ LANG_WNUM(sizeof(dirs)) +
	     " doorways leading out to the "+
	     COMPOSITE_WORDS(dirs) +".";
    }
}

#if 1
public mixed
out_dir(void)
{
    int   which, out, mem;

    sscanf(file_name(TO), MAZE + "maze%d", which);

    if (!which)
      return 0;

    out = way_out[which];

    if ((mem = member_array(MAZE + "maze" + out,
       query_exit_rooms())) < 0)
      return 0;

    return query_exit_cmds()[mem];
}
#endif
