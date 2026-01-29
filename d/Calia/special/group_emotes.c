
/*
    Group emotes for krougs, included into the kroug brain. 
  
    Coded by Maniac
*/


static string *group_things = 
    ({ "do a kroug war bounce!", 
       "execute a kroug battle strut!", 
       "carry out a kroug melee spin!", 
       "scream: We fear no-one!", 
       "shout: Hit! two, three, four, Hit!", 
       "cry: Thump! one, two, three, Thump!",  
       "chant: You Only Sing When-You're-Winning!",  
       "chant: We're On-The-March With Krougie's Aaarrrmy!", 
       "chant: You're Going Off In-A-Coffin!", 
       "chant: Always Look-On The Bright Side-Of-Death!", 
       "chant: One Kroug Went-To-Kill, Went-To-Kill A Calian.", 
       "chant: Are You-Watching-Thicky-Hurn?" }); 

void
group_emote(object *krougs, object *players)
{
    string comment;
    int ks, ps;

    ks = sizeof(krougs);
    ps = sizeof(players);
    if ((!ps) || (ks < 2))
        return;
   
   comment = group_things[random(sizeof(group_things))]; 

   tell_room(environment(krougs[0]), 
            capitalize(COMPOSITE_LIVE(krougs)) + " " + comment + "\n");  
}

