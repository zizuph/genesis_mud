#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <wa_types.h>

/*
int
filter_sword(object x)
{
    return ((function_exists("create_object", x) == "/std/weapon")
           && (x->query_wt() == W_SWORD));
}
*/

int
team_stay()
{
    object *team_obs;
    if (TP->query_team_leader() != TP)
        NFN0("But you are not the leader of the team.");
    team_obs = TP->query_team_others();
    if (!sizeof(team_obs))
        NFN0("But you are not in a team!");
    team_obs = filter(team_obs, present);
    if (!sizeof(team_obs))
        NFN0("But none from your team are with you anymore!");
    actor("You motion with your hand for your team to stay here.");
    target(" motions with " + POSSESSIVE(TP) + " hand for the team "
      + "to stay here.", team_obs);
    all2actbb("  motions with " + POSSESSIVE(TP) + " hand for", team_obs,
      " to stay here.");
    return 1;
}

int
team_whisper(string str)
{
    object *team_obs;
    team_obs = TP->query_team_others();
    if (!strlen(str))
        NFN0("Whisper what to your team-mates?");
    if (!sizeof(team_obs))
        NFN0("But you are not in a team!");
    team_obs = filter(team_obs, present);
    if (!sizeof(team_obs))
        NFN0("But none of your team-members are present!");
    actor("You whisper to your team-mate"
      + ((sizeof(team_obs) > 1) ? "s" : "") + ": " + str);
    target(" whispers to the team: " + str, team_obs);
    all2actbb("  whispers something to", team_obs, ".");
    return 1;
}

int
team_direct(string str)
{
    object *team_obs;
    if (!strlen(str))
        NFN0("What direction?");
    if (member_array(str, ({"east", "west", "south", "north", "up", "down",
        "northeast", "northwest", "southeast", "southwest"})) < 0)
        NFN0("That direction doesn't make sense.");
    team_obs = TP->query_team_others();
    if (!sizeof(team_obs))
        NFN0("But you are not in a team!");
    team_obs = filter(team_obs, present);
    if (!sizeof(team_obs))
        NFN0("But there are no team-member here!");
    actor("You motion for the team to go " + str + ".");
    target(" motions for the team to go " + str + ".", team_obs);
    all2actbb("  motions for", team_obs," to go " + str + ".");
    return 1;
}

