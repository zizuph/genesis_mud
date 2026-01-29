/*
 *  /d/Sparkle/obj/magic_map.c
 *
 *  This magic map is intended to be a major feature throughout Genesis.
 *  It will be given out by Lars to new players when they enter the
 *  game, and they can examine it to see maps of locations they are
 *  in with a "you are here" marker that moves when they do. To get
 *  information on how to set up your areas to function with the map,
 *  please read the file:
 *
 *    /d/Sparkle/open/magic_map.txt
 *
 *  Created March 2008, by Cooper Sherry (Gorboth)
 *    Much thanks to Novo for his excellent help with this project.
 */
#pragma strict_types
inherit "/std/object";

#include "../defs.h"
#include <stdproperties.h>

/* Global Variables */
public mapping     Map_Coordinates = ([]),
                   Sub_Map_List;
public string      Text_Map_File;


/* Prototypes */
public void        create_object();
public string      look_at_map();
public string *    load_text_map(string mfile, string msection = "main");
public void        draw_map(object who, string *which_map, int x, int y, int zoom = 0);
public int         display_full(object player, int zoom = 0);
public int         map_action(string arg);
public int         maphelp(string arg);
public int         mapexample(string arg);
public void        init();

public void        set_sub_map_list(mapping * m)  { Sub_Map_List   = m; }
public void        set_text_map_file(string s)    { Text_Map_File = s; }
public string      query_text_map_file() { return Text_Map_File; }


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("map");
    add_name( ({ "_sparkle_magic_map" }) );

    add_adj( ({ "magic" }) );
    
    set_short("magic map");
    set_long(look_at_map);

    add_cmd_item( ({ "map", "magic map", "the map", "the magic map" }),
                  ({ "read" }), look_at_map);

    add_prop(OBJ_I_NO_DROP, "It is far too useful to throw away!\n");
    add_prop(OBJ_I_NO_SELL, "You'd better keep it. Too useful!\n");
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_WEIGHT, 1);

    setuid();
    seteuid(getuid());
} /* create_object */


/*
 * Function name:        look_at_map
 * Description  :        this is called when people try to examine or
 *                       read the map. If a map file has been defined
 *                       for the room the player is in, the map is
 *                       displayed and a null string returned. If not,
 *                       a message indicating that the map is blank is
 *                       returned as text.
 * Returns      :        string - null on success, text otherwise
 */
public string
look_at_map()
{
    mixed  themapfile = environment(this_player())->query_prop(
                            "_room_s_test_map");
    

    if (themapfile)
    {
        display_full(this_player(), 1);
        return "";
    }

    return 
 "          _______________________________________________  __________\n"
+"     _   /                                               |/          |\n"
+"    | \\_/                                                            |\n"
+"   /                                                                 |\n"
+"  |                                                                  |\n"
+"  |                                                                  |\n"
+"  `.                                                                 |\n"
+"  '                                                                  |\n"
+"  |                                                                  |\n"
+"  |                                                                  |\n"
+"  |                                                                  |\n"
+"  |                                                                  |\n"
+"  |                 The map appears completely blank.                |\n"
+"  |                                                                  |\n"
+"  |              (You may type <maphelp> to learn more)              |\n"
+"  |                                                                  |\n"
+"  |                                                                  |\n"
+"  |                                                                  |\n"
+"  |                                                                  |\n"
+"  |                                                                  |\n"
+"  |                                                                  |\n"
+"  |                                                                  |\n"
+"  |                                                                  |\n"
+"  |                                                                  |\n"
+"  |                                                                  |\n"
+"  |                                                     _            |\n"
+"  |                                                _/|_/ |           |\n"
+"  |_______________________________________________/      |___________|\n";
} /* look_at_map */




/*
 * Function name:        load_text_map
 * Description  :        Read the contents of a text file. The first
 *                       section of the file contains data we will convert
 *                       into the global mapping Map_Coordinates. Following
 *                       these data is the map itself which we will load
 *                       into an array line by line.
 * Arguments    :        string mfile - the text file that contains the
 *                                      map we want to use.
 *                       string msection - the section of the map we want
 *                                         to draw. The default is to
 *                                         draw the "main" map.
 * Returns      :        string array - the map in array form
 */
public string *
load_text_map(string mfile, string msection = "main")
{
    int     i = 0;
    string *textmap_array,
            mfile_text = read_file(mfile),
           *mfile_sections,
           *mfile_data,
           *mfile_mapping_data,
           *mfile_mapping_entry,
           *coord_array;
    mapping zoom_sections = ([]);

    /* We ask that the info files separate different map sections by
     * two blank lines. Therefore, lets split according to that to
     * begin with.
     */
    TELL_G("mfile = " + mfile);
    TELL_G("msection = " + msection);
    TELL_G("strlen of mfile_text = " + strlen(mfile_text));
    mfile_sections = explode(mfile_text, "::NEWMAP::");

    /* Then, within each individual map section, we want to find the
     * map title for that zone, and write it to a mapping.
     */
    foreach(string zoom_section : mfile_sections)
    {
        mfile_data = explode(zoom_section, "\n\n");
        zoom_sections += ([ mfile_data[0] : i ]);
        i++;
    }

    TELL_G("Dumping zoom_sections");
    dump_array(zoom_sections);

    /* Now, since we have a mapping to connect the specific zone to
     * a specific map and data set, we divide the specific section
     * of info by blank lines.
     */
    mfile_data = explode(mfile_sections[zoom_sections[msection]], "\n\n");
    mfile_mapping_data = explode(mfile_data[1], "\n");

    /* Now, we write to the global variable the data coordinates that
     * correspond to the players location for the specific map we
     * are using.
     */
    foreach(string mdata : mfile_mapping_data)
    {
        mfile_mapping_entry = explode(mdata, " ");
        coord_array = ({});

        for (i = 0; i < sizeof(mfile_mapping_entry); i++)
        {
            switch (i)
            {
                case 1:
                case 2:
                    coord_array += ({ atoi(mfile_mapping_entry[i]) });
                    break;
                case 3:
                    coord_array += ({ mfile_mapping_entry[i] });
                    break;
                case 0:
                default:
                    break;
            }
        }

        Map_Coordinates += ([ mfile_mapping_entry[0] : coord_array ]);
    }

    textmap_array = explode(mfile_data[2], "\n");

    for (i = 0; i < sizeof(textmap_array); i++)
    {
        textmap_array[i] += "\n";
    }

    return textmap_array;
} /* load_text_map */


/*
 * Function name:        draw_map
 * Description  :        This is Novo's improvement on my earlier methods.
 *                       It takes an existing map and draws both the
 *                       point at which the player stands and bolds the
 *                       borders of the section of the map the player
 *                       is in.
 * Arguments             object  who - the player to draw to
 *                       string  which_map - the array containing the
 *                                           text lines of the map
 *                       int x - the x coordinate on the map
 *                       int y - the y coordinate on the map
 *                       (both of these represent where the player stands)
 *                       int zoom - true if this is a zoomed-in map,
 *                                  in which case we do not use
 *                                  the borders. Default = false.
 */
public void
draw_map(object who, string *which_map, int x, int y, int zoom = 0)
{
    string *newmap      = allocate(sizeof(which_map)),
            zoom_footer,
            norm_footer;
    int     index       = 0,
            edgex       = x,
            edgey       = y,
            startx,
            starty,
           *deltas      = ({ 0, 1, -2, 0, 0, -1, 2, 0 }),
            deltapos    = 2,
            match       = 1,
            testx,
            testy;

    zoom_footer =
 "==================================[Legend]====================================\n"
+"     - o -  Room locations and obvious direction exits\n"
+"     - * -  Room you are current standing in\n"
+"==============================================================================\n"
+"     The <zoom> command displays a less-detailed map of the larger area.\n";

    norm_footer =
 "==================================[Legend]====================================\n"
+"     . . .  Borders of the various zones (shown as X if you are within)\n"
+"     - o -  Room locations and obvious direction exits\n"
+"     - * -  Room you are current standing in\n"
+"==============================================================================\n";

    /* Make a copy of the map */
    foreach (string line:which_map)
    {
        newmap[index] = line;
        index++;
    }
       
    if (y <  sizeof(newmap)    &&
        y >= 0                 &&
        x <  strlen(newmap[y]) &&
        x >= 0                 &&
       !zoom)
    {

        /* Find the closest starting dot to the left of out point. */
        while (edgex                >= 0 &&
               newmap[edgey][edgex] != '.')
        {
            edgex--;
        }

        if (edgex < 0)
        {
            write("You do not appear to be in the boundaries of town!\n");
        }
        else
        {
            startx = edgex;
            starty = edgey;

            /* Match indicates we found a dot and need to make another. */
            while (match)
            {
                /* Mark the edge. */
                newmap[edgey] = (edgex ?newmap[edgey][..edgex - 1] : "" )
                              + "X" + newmap[edgey][edgex + 1..];
                
                match = 0;                

                /* We will try to make a left turn first.
                 * Then we will check the other directions -
                 * straight line, right turn, backwards.
                 */
                deltapos = (4 + deltapos) % (sizeof(deltas));
                //write("Pos "+edgex+","+edgey+"-"+deltapos+"\n");
                    
                for (int i = 0; i < 4; i++)
                {
                    
                    deltapos = (2 + deltapos) % (sizeof(deltas));

                    /* Try to find the next dot. */
                    testx = edgex + deltas[deltapos];
                    testy = edgey + deltas[deltapos + 1];
                    
                    if (startx == testx && starty == testy)
                    {
                       break;
                    }
                    
                    //write("Testing "+testx+","+testy+"-"+deltapos+"\n");
                    if (testy < sizeof(newmap) && testy >= 0 
                     && testx < strlen(newmap[testy]) && testx >= 0
                     && newmap[testy][testx] == '.')
                    {
                        edgex = testx;
                        edgey = testy;
                        match = 1;                        
                        break;
                    }
                }
            }
        }
    }

    newmap[y] = newmap[y][..x-1] + "*" + newmap[y][x+1..];
    
    foreach (string line:newmap)
    {
        who->catch_tell(line);
    }

    who->catch_tell( (zoom) ? zoom_footer : norm_footer);

    return;
} /* draw_map */


/*
 * Function name:        display_full
 * Description  :        This displays the map of Sparkle, zoomed out,
 *                       so that the player can see what part of town
 *                       they are currently in.
 * Arguments    :        object player - the person with the map
 *                       int zoom - true if we want to zoom to the
 *                                  appropriate sub-map for the room
 *                                  this player is in. Default = false.
 * Returns      :        int 1 - success always
 */
public int
display_full(object player, int zoom = 0)
{
    mixed  *coordinates;
    string *which_map,
            streetpath,
            text_map_file = environment(player)->query_prop(
                "_room_s_test_map");

    TELL_G("Text_Map_File = " + text_map_file);

    if (!text_map_file)
    {
        write("The map is blank, and thus you cannot <zoom> out"
          + " to a larger view.\n");
        return 1;
    }

    which_map = load_text_map(text_map_file);

    /* To get the name (alone) of the room the player is in, we have to
     * remove all the "/d/Domain/path/" stuff.
     */
    streetpath  = explode(file_name(
                  environment(this_player())), "/")[-1..][0];
    coordinates = Map_Coordinates[streetpath];

    TELL_G("streetpath = " + streetpath);
    dump_array(coordinates);

    if (zoom)
    {
        which_map = load_text_map(text_map_file, coordinates[2]);
        coordinates = Map_Coordinates[streetpath];

        TELL_G("Zoom true!");
        dump_array(coordinates);

        draw_map(this_player(), which_map, coordinates[0],
                 coordinates[1], 1);

        return 1;
    }

    draw_map(this_player(), which_map, coordinates[0], coordinates[1]);

    return 1;
} /* display_full */


/*
 * Function name:        map_action
 * Description  :        Action for the player to use to trigger the
 *                       map_module
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        1 - success always
 */
public int
map_action(string arg)
{
    display_full(this_player());

    return 1;
} /* map_action */


/*
 * Function name:        maphelp
 * Description  :        Give the player feedback on how to participate
 *                       in the process of expanding the mapping of
 *                       the game
 * Arguments    :        string arg - what he player typed after the
 *                                    verb.
 * Returns      :        int 1
 */
public int
maphelp(string arg)
{
    write("If the map is blank when you examine it this is because no one"
      + " has yet taken the time to create a high-quality map of the area"
      + " you are currently in and integrated it into the game. If you"
      + " feel skilled in creating maps out of text, please feel free to"
      + " see what you can come up with. Create a text-based map of the"
      + " area you are in. You can type <mapexample> to see an example"
      + " of the sort of quality we are after. Then, send it to the"
      + " responsible wizards by typing <mail aop> in your nearest"
      + " post office. Who knows, the map you create might become a"
      + " permenant part of the game!\n");

    return 1;
} /* maphelp */


/*
 * Function name:        mapexample
 * Description  :        Give the player feedback on what a good
 *                       text-based map might look like
 * Arguments    :        string arg - what he player typed after the
 *                                    verb.
 * Returns      :        int 1
 */
public int
mapexample(string arg)
{
    write(
 "                      . . . . . . . . . . . . .\n"
+"                      .     Farmlands       ~~.\n"
+"                      . \" _\"___\" _  __\"\"_ ~~~ .\n"
+"                      . __\"__\"\"_\"___\"_\"  ~~~  .\n"
+". . . . . . . . . . . . .  o _\"__\"_\"__  ~~~   .\n"
+".                       .  | _\"\"\"_  _\"  ~~~ . . . . . . . . . . .\n"
+".  ^. ^.                .  o \"\"_\"___\"_ ~~~  .        \"\"         .\n"
+".    `. `^.^._.^.       .  |           ~~~  .     \"@@@@\"@@      .\n"
+".[]--'--[]  Northern    .  o      o    ~~~  .  \" @@\" \"\" @@@\"@   .\n"
+".|| /^\\ || Mountains    .  |     /     ~~~  . @@\"@  The \"@@@\"\"  .\n"
+".||_|I|_||^.       o - o.- o - o - - -|---|-.- o - Sterling \"@  .\n"
+".    ^.^.   `^.^.       .  |           ~~~  .  @ @  Woods  @@\"  .\n"
+".      ` `._.^.` `.     .  o           ~~~  . @@\" \"@\" \"\" \"@@\"   .\n"
+".                       . .|. . . . . .~.~. .  \" @\"@@@ \" @@@@   .\n"
+". . . . . . . . . . . . .  o    .      ~~~  .     \"@@ \"@  \"     .\n"
+"      .                    |    .      ~~~  . . . . . . . . . . .\n"
+"      .                    o    .      ~~~\n"
+"      .      Village       |    .      ~~~\n"
+"      .         of         o    .      ~~~\n"
+"      .    Greenhollow     |    .      ~~~      -------------\n"
+"      .                    o    .      ~~~      MAP OF TUTORI\n"
+"      .                  /      .       ~~~         ISLE\n"
+"      .        o - o - o        .       ~~~     -------------\n"
+"      .            |            .        ~~~\n"
+"      .            o            .         ~~~\n"
+"      .            |            .           ~~~\n"
+"      .            o  Hilltop   .             ~~~~~\n"
+"      .          .`|`.          .                ~~~~~~~\n"
+"      .         ;  o  :         .                      ~~~~~~~~~\n"
+"      . . . . .'. . . .`. . . . . \n");

    return 1;
} /* mapexample */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(mapexample, "mapexample");
    add_action(maphelp, "maphelp");
    add_action(map_action, "zoom");
} /* init */