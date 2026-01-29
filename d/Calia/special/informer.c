
/* 
   The Calian Informer, sort of an automated note writer who delivers
   reports on Kroug Raids. Included some nice ascii pics found at: 
   http://www.duc.auburn.edu/~norgapd/ in April '96

   Coded by Maniac

   History: 
            11/5/96     Made to use create_note    Maniac
            10/5/96     updated              Maniac
            11/4/96     Created              Maniac
*/

#pragma save_binary
#pragma strict_types
#pragma no_inherit

#include <stdproperties.h>
#include <language.h>
#include <composite.h>
#include "/d/Calia/sys/kroug.h"

inherit "/std/monster"; 


/* These piccies look a bit funny because one needs to add \ here and there */
string *pic1 = ({ 
"                    ",  
"       / \\      _-'    ", 
"     _/|  \\-''- _ /    ", 
"__-' { |          \\    ", 
"    /             \\    ", 
"    /       \"o.  |o }  ", 
"    |            \\ ;   ", 
"                  ',   ", 
"       \\_         __\\  ", 
"         ''-_    \\.//  ", 
"           / '-____'   ", 
"          /          ", 
"        _'        ", 
"      _-'       ", 
"           ", }); 


string *pic2 = ({ 
"           _,.-----.,_      ", 
"        ,-~           ~-.     ", 
"      ,^___           ___^.   ", 
"     /~\"   ~\"   .   \"~   \"~\\    ", 
"    Y  ,--._    I    _.--.  Y    ", 
"    | Y     ~-. | ,-~     Y |    ", 
"    | |        }:{        | |    ", 
"    j l       / | \\       ! l    ", 
" .-~  (__,.--\" .^. \"--.,__)  ~-.   ", 
"(           / / | \\ \\           )   ", 
" \\.____,   ~  \\/\"\\/  ~   .____,/    ", 
"  ^.____                 ____.^    ", 
"     | |T ~\\  !   !  /~ T| |      ", 
"     | |l   _ _ _ _ _   !| |    ", 
"     | l \\/V V V V V V\\/ j |    ", 
"     l  \\ \\|_|_|_|_|_|/ /  !    ", 
"      \\  \\[T T T T T TI/  /     ", 
"       \\  `^-^-^-^-^-^'  /      ", 
"        \\               /     ", 
"         \\.           ,/    ", 
"           \"^-.___,-^\"   ", 
"                      ", }); 


string *pic3 = ({ 
"   |^^^|  ", 
"    }_{   ", 
"    }_{      ", 
"/|_/---\\_|\\    ", 
"I _|\\_/|_ I    ", 
"\\| |   | |/    ", 
"   |   |     ", 
"   |   |   ", 
"   |   |   ", 
"   |   |   ", 
"   |   |   ", 
"   |   |   ", 
"   |   |   ", 
"   |   |   ", 
"   |   |   ", 
"   |   |   ", 
"   |   |   ", 
"   |   |   ", 
"   |   |   ", 
"   \\   /   ", 
"    \\ /   ",
"     Y   ", 
"       ", }); 


string *pic4 = ({ 
"        +       ", 
"  *    / \\    *   ", 
" OnO  :xxx:  OnO   ", 
" I I   I I   I I   ", 
" I I   I I   I I   ", 
"O_O_O_O_O_O_O_O_O  ", 
"\\_______________/  ", 
" I     ___     I  ", 
" I    / i \\    I  ", 
" I   I: i :I   I  ", 
" I___I:_i_:I___I  ", 
"                 ", });  


int active, 
    total_time, 
    total_krougs; 
int *champion_kills; 

string *casualties = ({ });  
string intro, additional, board_room, champion, *slayers, note; 

object the_board;


/* For special comments */
void
set_board_room(string str)
{
     board_room = str; 
}


/* For special comments at end of note */
void
set_additional(string str)
{
     additional = str; 
}


/* For special comments at start of note */
void
set_intro(string str)
{
     intro = str; 
}


void
set_champion(string str)
{
    champion = str;
}


void
set_slayers(string *s)
{
    slayers = s;
}


void
set_total_time(int t)
{
    total_time = t;
}


void
set_champion_kills(int *k)
{
    champion_kills = k;
}

void
set_total_krougs(int t) 
{
    total_krougs = t;
}


void
set_casualties(string *c) 
{
    casualties = c;
}


private int
generate_note()
{
    string *words, *pic, curr_line, tmp, ks, *ke; 
    object br;
    int i, wc;

    if (!stringp(board_room)) 
        return 0;

    board_room->load_me();
    if (!objectp(br = find_object(board_room)))
        return 0;

    words = ({ }); 
    if (stringp(intro))
         words += explode(intro, " "); 
    words += explode("The attacking force consisted of " + 
                 LANG_WNUM(total_krougs) + " krougs.", " "); 
    words += explode("The ensueing battle lasted " + 
                 LANG_WNUM(total_time) + " minutes.", " ");  
    if (sizeof(slayers)) 
        words += explode("The following slayers were in action: " + 
                     COMPOSITE_WORDS(slayers) + ".", " "); 

    if (strlen(champion) && (sizeof(champion_kills) == NUM_KROUG_TYPES)) {
        ks = "";
        ke = allocate(sizeof(champion_kills)); 
        for (i = 0; i < sizeof(champion_kills); i++) 
            ke[i] = (LANG_WNUM(champion_kills[i]) + " " +
                     KROUG_DESC(i, champion_kills[i])); 
        ks = (COMPOSITE_WORDS(ke) + ".");  
        words += explode("Congratulations go to " + champion + 
                        ", who was the champion kroug slayer, " +
                        "dispatching a total of " + ks, " "); 
    }

    words += explode("There " + 
                    ((sizeof(casualties) == 1) ? "was " : "were ") +  
                    LANG_WNUM(sizeof(casualties)) + " " + 
                    ((sizeof(casualties) == 1) ? "defender " : "defenders ") +  
                    "killed" + ((sizeof(casualties) == 0) ? "." : 
                    (", namely " + COMPOSITE_WORDS(casualties) + ".")), 
                    " ");  

    if (stringp(additional)) 
        words += explode(additional, " "); 

    note = ""; 

    switch (random(4)) {
        case 0 : pic = pic1; 
                 break;
        case 1 : pic = pic2;
                 break;
        case 2 : pic = pic3;
                 break;
        default : pic = pic4; 
                  break;
    }

    wc = 0;  

    /* Picture-wrapped part */
    for (i = 0; i < sizeof(pic); i++)  {
        tmp = pic[i];  
        curr_line = tmp;
        while ((strlen(tmp) < 70) && (wc < sizeof(words))) {
            tmp += (words[wc] + " "); 
            if (strlen(tmp) < 70) { 
                curr_line = tmp;
                wc++; 
            }
         }
         note += (curr_line + "\n"); 
    }

    if (wc < sizeof(words)) 
        note += break_string(implode(words[wc..(sizeof(words)-1)], " "), 70); 

    note += "\n\nThe Calian Informer.\n"; 
    return 1;
}


private void
leaveit()
{
     command("bow"); 
     tell_room(environment(this_object()), "Informer leaves in a puff " + 
              "of smoke.\n"); 
     remove_object(); 
}


private void
writeit()
{
     the_board->create_note("Kroug Raid Report.", "Informer", note);       
     command("emote finishes writing a note."); 
     set_alarm(1.0, 0.0, leaveit); 
}


private void
postit()
{
    string t; 

    the_board = present("board", environment(this_object()));      

    if (!objectp(the_board))
        return;

    seteuid(getuid(the_board)); 
    this_object()->command("emote starts writing a note."); 
    set_alarm(1.0, 0.0, writeit); 
}


private void
gothere()
{
     move_living("X", board_room); 
     this_object()->command("bow"); 
     set_alarm(1.0, 0.0, postit); 
}


private void
realactivate()
{
     if (!generate_note())    
         return;

     set_alarm(1.0, 0.0, gothere); 
}


void
activate()
{
     if (active)     
         return;

     active = 1;
     set_alarm(1.0, 0.0, realactivate); 
}


void
create_monster()
{
     set_name("informer");  
     set_living_name("informer"); 
     set_adj("informative"); 
     set_race_name("human"); 
     set_long("A very informative looking human.\n");  

     default_config_npc(50); 
     add_prop(OBJ_M_NO_ATTACK, 1); 
     add_prop(OBJ_M_NO_MAGIC_ATTACK, 1); 
     add_prop(LIVE_I_ALWAYSKNOWN, 1); 

     active = 0;
}

