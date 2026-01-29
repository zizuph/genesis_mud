/*               
 * The code for the Imladris healers guild songs.
 * Songs can be sung by typing ising <songname>:
 * 'Farewell', fall of 'Gil-galad',...
 *               
 * Some code is copied from the rangers guild.
 *               
 * Odin, 201194. 
 */              
                         
#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#define TR(x) tell_room(ENV(TP),x)

do_song(str)     
{                
    string songname;
    if (ghost()) return fail_ghost();
    if (!str)    
    return 0;
    if (sscanf(str, "%s", songname) == 1)
        return song(songname);
        return 0;
}

song(string songname)
{           
    if(songname=="Farewell" || songname=="farewell")
    {       
        write("You sadly start to sing a song of your departing.\n\n");
        say(QCTNAME(TP)+" sadly starts to sing a song of farewell.\n\n");
        TR("      Farewell we call to heart and hall!\n");
        TR("    Though wind may blow and rain may fall,\n");
        TR("    We must away ere break of day\n");
        TR("    Far over wood and mountain tall.\n\n");
        TR("      To Rivendell where elves yet dwell\n");
        TR("    In glades beneath the misty fell,\n");
        TR("    Through moor and waste we ride in haste,\n");
        TR("	And wither then we cannot tell.\n\n");
        TR("      With foes ahead, behind us dread,\n");
        TR("    Beneath the sky shall be our bed,\n");
        TR("    Until our toil be passed,\n");
        TR("    Our journey done our errand sped.\n\n");
        TR("      We must away! We must away!\n");
        TR("      We leave before the break of day!\n\n");
        say(QCTNAME(TP)+"'s voice fades and the song comes to an end.\n");
        return 1;
    }
    else
    {
         write("You start to sing a song, but dont remember the text...so you stop.\n");
         say(QCTNAME(TP)+" starts to sing a song, but it seems "+HE_SHE(TP)+" has forgotten the text and stops.\n");
         return 1;
     }
     NF("You dont remember such a song.\n");
     return 0;
}

fail_ghost()
{
    write("You're dead meat! You can't do that.\n");
    return 1;
}
                
ghost()
{
    return TP->query_ghost();
}                                               















                          
