/* These defines are needed by the scroll objects */
/* must define LANG_LEVEL before include this file   */
/* levels based on max = super journey lang in adv guild in Krynn (50) */
 
#define MORE_OBJ "/std/board/board_more"
#define ALPHA_LANG_LEVEL    1
#define BETA_LANG_LEVEL     5
#define GAMMA_LANG_LEVEL   10
#define DELTA_LANG_LEVEL   15
#define EPSILON_LANG_LEVEL 20
#define ZETA_LANG_LEVEL    25
#define ETA_LANG_LEVEL      1
 
 
/*
 * Function name: read_it (overrides read_it in std/scroll.c)
 * Description:   Perform the actual read
 * Comments: Slightly modified to include check for language level
 */
void
read_it(string str)
{
    seteuid(getuid(this_object()));
    say(QCTNAME(this_player())+" reads the "+QSHORT(this_object())+".\n");
    if (!scroll_file)
        write("There was nothing to read in that book.\n");
    else if (str == "read")
       {
       if (this_player()->query_skill(SS_LANGUAGE) < LANG_LEVEL)
          write("You can not understand the ancient Argosian writing.\n");
       else
          cat(scroll_file);
       }
    else
        clone_object(MORE_OBJ)->more(scroll_file, 2);
}
