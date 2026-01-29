/*
 * Defensive weaving (Dex)
 *
 *   This enables the living to duck and weave instead of attacking, thereby
 *   making the subject likely to fumble.
 *
 *   To make this work, we'll have to make funny fumble results.
 *
 */

varargs int
start_weaving(object who)
{
    if (!who) 
        who = previous_object();
    add_cont_fumble(who,
	"You are ducking and weaving to prevent attacks!\n");
}

int
stop_weaving(object who)
{
    remove_cont_fumble(who,
	"You are ducking and weaving to prevent attacks!\n");
}
