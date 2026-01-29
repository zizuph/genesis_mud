/*
 * guild_defs.h
 * 
 * Handy definitions, shared by every file in the guild.
 * Cedric 3/93
 */
 
/*
 * SG_INSTRUMENTAL      The instrumental skill..how well can s/he play?
 * SG_READ_MUSIC        The ability to read music..namely, the Songs of Power.
 * SG_VOCAL             The vocal skill..how well can s/he sing?
 * SG_TUNE_REPAIR       The ability to tune/repair one's instrument.
 * 
 * MUSE         The number of the player's Muse:
 *                          1) Thalia       Comedy
 *                          2) Calliope     Epic poetry
 *                          3) Melpomene    Tragedy
 *                          4) Clio         History
 *
 * SG_FAKE_SKILL        A hack used within the song code.
 * SG_VOCAL_DAMAGE      The damage level of the player's voice. 0=healthy.
 * SG_FLAG              Several flags compounded into one integer:
 *                	Bells, Ballads, Dias, Mood, and Muse.
 */
#define BS(message)     break_string(message,76)
#define TP              this_player
#define TO              this_object
#define GUILD           "/d/Terel/cedric/guild/"
#define GUILDOBJ        GUILD+"obj/"
#define GUILD_NAME      "The August Order of Minstrels"
#define GUILDMASTER     "cedric"
#define MEMBER(xx)      xx->query_guild_member(GUILD_NAME)
#define NF(xx)		notify_fail(xx)
#define CM(xx)		catch_msg(xx)

#define SG_INSTRUMENTAL 130050
#define SG_VOCAL        130051
#define SG_READ_MUSIC   130052
#define SG_TUNE_REPAIR  130053

#define SG_FAKE_SKILL   130055
#define SG_VOCAL_DAMAGE 130056
#define SG_FLAG         130057

#define MUSE1           "Thalia"
#define MUSE2           "Calliope"
#define MUSE3           "Melpomene"
#define MUSE4           "Clio"

#define MUNDANEDIR      GUILD+"mundane/"
#define BALLADDIR       GUILD+"ballad/"
#define POWERDIR        GUILD+"power/"

/*
 * Flags:
 */
#define MOODMASK        15
#define BELLMASK        16
#define DIASMASK        32
#define BALLADMASK      64
#define MUSEMASK        896     /* 128+256+512 ... three consecutive bits */
#define MUSEMASKBASE    128     /* lowest bit in the series */

/*
 * Moods:
 */
#define NORMAL      0
#define SERIOUS     1
#define JOVIAL      2
#define BRAVE       3
#define CONVERSE    4
#define SAD         5
#define ANGRY       6
#define SONG        7


/*
 * Function:    parse_song
 * Description: Takes a string of the pattern "<type> <which>", where <type> is
 *              the type (mundane, ballad, or power) of the song desired and
 *              <which> is the number, title, or first word of the title of
 *              that song, and returns the filename of the song.
 * Arguments:   
 *      type - the type string. If empty, parse_song will attempt to
 *             draw a type from the which string.
 *              which - the which string to be processed.
 *              m_arr - the array containing Mundane Songs to be looked up.
 *              b_arr - the array containing Ballads to be looked up.
 *              p_arr - the array containing Songs of Power to be looked up.
 * Returns:     0 if unsuccessful, else the path+filename of the song.
 * NOTE:        Sets own notify_fail messages.
 */
mixed
parse_song(string type, string which, string *m_arr, string *b_arr, string *p_arr)
{
    int i;
    string  *the_arr, *words, the_string, the_dir, 
            title, first_word, second_word;

    setuid();
    seteuid(getuid());
    if (type=="")
        if(!sscanf(which,"%s %s",type,which))
            return 0;

    if (type=="ballad"||type=="mundane"||type=="power")
    {
        switch (type)
        {
            case "ballad":
                the_dir = BALLADDIR; the_arr = b_arr; the_string = "Ballad";
                break;
            case "mundane":
                the_dir = MUNDANEDIR; the_arr = m_arr; the_string = "Mundane Song";
                break;
            case "power":
                the_dir = POWERDIR; the_arr = p_arr; the_string = "Song of Power";
                break;
        }
        if (sscanf(which, "%d", i))
        {
            if (i>sizeof(the_arr))
            {
                notify_fail("No "+the_string+" with that number!\n");
                return 0;
            }
            return the_dir+the_arr[i-1];
        }
        for (i=0;i<sizeof(the_arr);i++)
        {
            if (strlen(read_file(the_dir+the_arr[i],1,1)))
            {
                if (the_arr == p_arr)
                    title = explode(read_file(the_dir+the_arr[i],1,1),"**")[1];
                else
                    title = explode(read_file(the_dir+the_arr[i],1,1),"**")[0];

                words = explode(title+" ", " ");
                first_word = explode(title+" ", " ")[0];

                if (member_array(first_word, ({"a", "an", "the"}))!=-1)
                    second_word = explode(title+" ", " ")[1];
                else
                    second_word = "";
                if (title==which || which==first_word || which==second_word)
                {
                    return the_dir+the_arr[i];
                }
            }
        }
    }
    notify_fail("Refer to songs as: <type> <song>\n"
    + "where <type> is mundane, ballad, or power,  and song is the number, title\n"
    + "(in lowercase), or first word of the title of the song you wish to read.\n");
    return 0;
}

/*
 * Function:    cap_title
 * Description: Takes a song file and returns the capitalized title of the 
 *              song, plus a trailing space.
 */
string
cap_title(string song_file)
{
    string trash, title, newtitle, *title_words;
    int size,j;
    
    if (sscanf(song_file, POWERDIR+"%s", trash))
        title = explode(read_file(song_file,1,1),"**")[1];
    else
        title = explode(read_file(song_file,1,1),"**")[0];
    newtitle = "";
    size = sizeof(title_words = explode(title+" "," "));
    for (j=0;j<size;j++)
        newtitle+=capitalize(title_words[j])+" ";
    return newtitle;
}

/*
 * Function:    on_line
 * Description: Returns an array of every minstrel currently on-line. Used
 *              by a number of Minstrel abilities that reach the ears of 
 *              all guild members.
 * Returns:     Array of objects, each of which is an on-line minstrel.
 */
object
*on_line()
{
    object *folks, *guilds;
    int i;
    
    guilds = ({});
    folks = users();
    for (i=0;i<sizeof(folks);i++)
        if (MEMBER(folks[i]))
            guilds += ({folks[i]});
    return guilds;
}

/*
 * Function:	comment_filter
 * Description:	Filters out lines begining with a "#" sign
 * Usage:	ARR = filter(ARR, "comment_filter", this_object);
 *		where ARR is the array of lines you wish to filter.
 */
int
comment_filter(string line)
{
    if (line[0] == '#') 
	return 0;
    else 
	return 1;
}
