#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <language.h>
#include <macros.h>

private int *globes;

public int
query_globe_x(int globenum)
{
    return globes[(globenum-1)*2];
}

public int
query_globe_y(int globenum)
{
    return globes[(globenum-1)*2+1];
}

public int
place_globe(int globenum, int xpos, int ypos)
{
    int i;

    if ((xpos < 1) || (xpos>8) || (ypos<1) || (ypos>8))
        return -1;

    for (i=0; i<8; i++)
        if ((globes[i*2] == xpos) && (globes[i*2+1] == ypos))
            return 0;

    globes[(globenum-1)*2] = xpos;
    globes[(globenum-1)*2+1] = ypos;
    return 1;
}

public int
conflict_globe(int globenum, int globenum2)
{
    int x, y;
    x = ABS(query_globe_x(globenum) - query_globe_x(globenum2));
    y = ABS(query_globe_y(globenum) - query_globe_y(globenum2));
    if ((!x) || (!y) || (x == y))
        return 1;
    return 0;
}

public int
puzzle_solved()
{
    int i, j;
    for (i = 1; i<= 7; i++)
        for (j = i+1; j <=8; j++)
            if (conflict_globe(i, j))
                return 0;
    return 1;
}

public string
word_conflict(int globenum)
{
    int i, j, *k, conflicts;
    string retval, endval;

    k = ({});

    for (i = 1; i <= 8; i++)
        if ((globenum != i) && (conflict_globe(globenum, i)))
            k += ({ ++j });
        else
            k += ({ 0 });

    retval = "The " + LANG_WORD(globenum) + " globe is not pierced by " +
        "any light.\n";
    endval = "";

    if (j)
    {
        retval = "The " + LANG_WORD(globenum) + " globe is pierced by " +
            "light from the ";
        if (j>1)
            endval = "globes.\n";
        else
            endval = "globe.\n";

        for (i = 0; i<8; i++)
        {
            if (k[i])
            {
                if (j>2)
                    retval += LANG_WORD(i+1) + ", ";
                else
                    if (j>1)
                        retval += LANG_WORD(i+1) + " and ";
                    else
                        retval += LANG_WORD(i+1) + " ";
                j--;
            }
        }

    }
    return retval + endval;
}

public void
create_object()
{
    globes = ({ 1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8, });

    set_long("This is a square board which is full of holes.  Each side " +
        "has eight holes, so there are sixty-four holes in all.  In " +
        "eight of those holes are glowing globes.  You can 'scan' the " +
        "board to see the positions of all the globes.\n");
    set_name("board");
    set_adj("silverwood");
    add_name("q_puzzle_board");
    set_no_show_composite(1);
    
    add_prop(OBJ_M_NO_GET, "The board is firmly attached to the floor.\n");
    add_item(({ "globes", "glowing globes" }),
        "These are small glowing globes of blue light.  Each of the " +
        "eight emits light in eight directions, along the cardinal " +
        "points and the diagonals.\n");
}

public void
init()
{
    ::init();
    add_action("get_globe", "get");
    add_action("move_globe", "slide");
    add_action("scan_globes", "scan");
    add_action("check_globe", "examine");
    add_action("check_globe", "exa");
}

public int
move_globe(string arg)
{
    int globenum, newx, newy;
    string whichgl, whichdir;

    notify_fail("Slide what?\n");
    if (!strlen(arg))
        return 0;

    notify_fail("The correct syntax is 'slide the number " +
        "(e.g. first) globe to the direction'  Direction can be right, " +
        "left, forward, or backward.\n");
    if (!parse_command(arg, this_player(), "[the] %w [glowing] " +
        "'globe' [to] [the] %w", whichgl, whichdir))
        return 0;
    
    globenum = LANG_ORDW(whichgl);

    notify_fail("Slide which globe?\n");
    if ((!globenum) || (globenum > 8))
        return 0;

    newx = query_globe_x(globenum);
    newy = query_globe_y(globenum);

    notify_fail("Slide the globe which direction?\n");
    switch (whichdir)
    {
        case "left": newx--; break;
        case "right": newx++; break;
        case "forward": newy--; break;
        case "backward": newy++; break;
        default: return 0;
    }

    switch (place_globe(globenum, newx, newy))
    {
        case -1: write ("You can't slide the globe off of " +
            "the board.\n"); break;
        case 0: write ("There is already a globe in that place.\n");
            break;
        case 1: write ("You slide the " + whichgl + " globe " +
            whichdir + ".\n");
    }

    if (puzzle_solved())
        environment(this_object())->open_puzzle_lock();
    else
        environment(this_object())->close_puzzle_lock();
    return 1;
}

public int
scan_globes(string arg)
{
    int i,x,y,globe_is;

    notify_fail("Scan what?\n");
    if (arg != "board")
        return 0;

    write ("\n");

    for(y=1; y<9; y++)
    {
      for(x=1; x<9; x++)
      {
        globe_is=0;
        for (i = 0; i < 8; i++)
          if((x==globes[i*2]) && (y==globes[i*2+1]))
            globe_is=i+1;
        if(globe_is)  write(" "+globe_is);
        else  write(" .");
      }
      write ("\n");
    }
    write ("\n");
    return 1;
}

public int
get_globe(string arg)
{
    if ((arg != "globe") && (arg != "globes") && (arg != "glowing globe")
        && (arg != "glowing globes"))
    return 0;

    write ("The globe seems too heavy to pick up, small as " +
        "it is, but it seems as though you could slide it.\n");
    return 1;
}

public int
check_globe(string arg)
{
    int globenum;
    if (!parse_command(arg, this_player(), "[the] %w [glowing] 'globe'",
        arg))
        return 0;

    globenum = LANG_ORDW(arg);
    if ((globenum<1) || (globenum > 8))
        return 0;

    write (word_conflict(globenum));
    return 1;
}

public void
enter_env(object to, object blah)
{
    ::enter_env(to, blah);
    to->add_my_desc("There is a silverwood board here, with " +
        "eight glowing globes of light resting on top of it.\n");
}

public void
reposition_globes()
{
    tell_room(environment(this_object()), "The board hums softly, and the " +
        "globes seem to slide by themselves.\n");
    globes = ({ 1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8 });
}
