inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat */

/* defines for types of hearts */
#define GHOUL 1
#define GOOD 2
#define DAGGER "/d/Kalad/common/wild/pass/citadel/wep/q_dagger"

int corpse_here;
object dagg;
object ring;
object kabal;
create_room()
{
    ::create_room();
    INSIDE;
    add_prop(ROOM_I_LIGHT,0);
    set_short("Within the dwarven city of Underhome");
    set_long("You have arrived at the burrial chamber with only one "+
        "exit from it; the way you came from. In the center you "+
        "see a large sarcophagus with the lid halfway pushed off. A "+
        "glimmer of light radiates out of it. Along the "+
        "southern wall two chandeliers stands with thick "+
        "candles in them, and a small altar placed in between them. "+
        "It seems to be dedicated to the God Thanar.\n");
    add_item(({"pictures","several pictures"}),
        "The pictures convey too much for you to take it "+
        "all in just by sweeping your eyes over them. "+
        "Maybe take a closer look on each of them? You "+
        "see eight in total.\n");
    add_item(({"coffin","sarcophagus"}),"It is a huge hollow "+
        "stone-block with several decorations on all four sides of it. "+
        "When you look inside, @@corpse@@\n");
    add_item("lid","The lid, a large flat stone, has been pushed off to "+
        "the side of the sarcophagus. You see several cracks in it "+
        "that must have been inflicted on it when it was removed.\n");
    add_item("decorations","They seem to tell a story; A story of "+
        "the life-span of the human that was put to rest in this "+
        "crypt. It is divided into several pictures that you can "+
        "look at closer.\n");
    add_item(({"first picture","picture 1","first story","first scene"}),
        "The first picture shows the birth of a boy child in "+
        "a small village named Thandyr, situated within the realm of "+
        "Imneria. He has the look of a man even as a newborn. A man of visions "+
        "and strength. The shadow cast by the small child looks "+
        "unnatural, as if it belongs to his soul rather than his "+
        "corpus:  large, embracing...and threatening.\n");
    add_item(({"second picture","picture 2","picture two"}),
        "This scene shows a young man on his knees in front "+
        "of a mighty divine force: the God Thanar. Kabal "+
        "is the child, now grown into a man, chosen to lead "+
        "Thanar's will in the battle against all demihumans.\n");
    add_item(({"third picture","picture 3","picture three"}),
        "A battlefield with Kabal, the warrior, standing victorious above "+
        "the corpses of the race of elves. His waraxe, glowing with an "+
        "unnatural grey colour, is "+
        "smeared with red blood. His men salutes him with raised "+
        "swords, darkened with the signs of a mighty battle. "+
        "The sun strikes the figure of Kabal, enhancing his "+
        "might as if he was bathed in divine power.\n");
    add_item(({"fourth picture","picture 4","picture four"}),"Gnomes and hobbits "+
        "are the victims in this scene. They are massacred in one "+
        "great battle led by an Avatar of Thanar and the now "+
        "human leader, Kabal. A combined force of elite demihumans "+
        "slays the Avatar in a terrible fight, but are themselves slain "+
        "to the last through the leadership of Kabal. "+
        "He is now shown as a warlord of great stature; He is "+
        "wearing marvellous mithril platemail, offered in "+
        "tribute to him from a dwarven king, and a grand shield "+
        "with a clenched fist engraved upon it.\n");
    add_item(({"fifth picture","picture 5","picture five"}),
        "This plaque shows the grand burial of the slain Avatar "+
        "in a secluded location in the Hespyre mountains, along "+
        "with several items of power carried by him in his "+
        "last battle. Kabal himself is overseeing the burial "+
        "as the superior leader of the grand race of humans. "+
        "True grief shows itself in the hardened features of Kabal's face.\n");
    add_item(({"sixth picture","picture 6","picture six"}),
        "This image shows Kabal standing on a large plain that "+
        "ends at a cliff next to the huge sea; he is "+
        "founding the city of Kabal. The burning sun seems to embrace "+
        "Kabal as he announces the new capital.\n");
    add_item(({"seventh picture","picture 7","picture seven"}),
        "This picture shows an old man, Kabal, on the "+
        "throne within the city he himself founded years before. "+
        "Kabal is shown as a man radiating power, wisdom and "+
        "royality. You notice a magnificant crown next to him, "+
        "symbolizing the royality Kabal has earned for himself, "+
        "but that he has decided to wait before claiming.\n");
    add_item(({"eight picture","picture 8","picture eight","last picture"}),
        "This last picture shows Kabal being slain by "+
        "other humans outside the city. Some deep dwarves find "+
        "the corpse and carry it to Underhome. Here Kabal is "+
        "given his burial, but as a final revenge, a drow priestess "+
        "cuts out the heart of the corpse during the time the remains, "+
        "according to dwarven custom, lie alone in a clean "+
        "cave for three nights. The burial of the corpse "+
        "is performed by dwarven priests, who end the ceremony with "+
        "prayers to their God Rhaxvan. Pictures of truth are carved "+
        "upon the sarcophagus "+
        "during their trance, telling the lifetale of the deceased. "+
        "On the edge of the picture, you see some letters carved "+
        "into the stone; carvings that shine like fresh blood:\n\n"+
        "Z'ress wun elghinn ulu lil ogglin del Quarvalsharess!\n"+
        "Elamshin; Draa colbauth.\n\n"+
        "Uss yochlol izil elgg-hor lueth uss belbau elghinn ulu lil ultrin.\n"+
        "Lil z'ress zhah wund lil qu'ilth del lil elghinn.\n"+
        "Natha z'ress vel'uss plynn dosst qu'ilth. Thalack!\n"+
        "Lil z'ress zhah wund lil qu'ilth del usstan.\n"+
        "Natha z'ress vel'uss plynn usstan qu'ilth. Elghinn!\n\n"+
        "Uss dru, uss elghinn.\n"+
        "Uss colbauth z'hin pholor lil z'ress del lil faerl velve.\n"+
        "Uss clbauth velkyn alust dos.\n\n"+
        "Wael, xun dosst ilindith! Ragar lil colbauth!\n");
    
    add_item(({"altar","altar of thanar"}),
        "The altar is made of some black, hard stone "+
        "that looks very unused. A layer of dust cover it "+
        "along with a red cloth that has seen better days.\n");
    add_item(({"cloth","red cloth"}),
        "It is a red torn-up cloth that once was a decoration of "+
        "the altar.\n");
    add_item(({"yard","graveyard"}),"You know the old graveyard, "+
        "dating back to the terrible wars of ancient times when the dwarves "+
        "lost so many of their men in violent combat, is to the north.\n");
    add_item(({"cirlce","circle of light","light"}),"In this area, "+
        "your lightsource manages to fight off the everlasting darkness "+
        "down here.\n");
    add_item(({"smell","acidious smell"}),"The smell seems to come from "+
        "the sarcophagus.\n");
    add_item(({"dark area","area"}),"The dark area is out of vision, so "+
        "all you really know about it is the chilling and acidious smell "+
        "the draft carries with it from there.\n");
    add_item("crypt","It is an old stone building, probably housing a long dead "+
        "hero or a lucky dwarf that found a gold-rich vein. The place gives you "+
        "a creepy feeling though.\n");
    add_exit(CPASS(dwarf/crypt/c25),"north",0,-1,-1);
    
    set_noshow_obvious(1);
    set_alarm(0.0,0.0,"reset_room");
}

reset_room()
{
    object o1,o2,o3,o4,o5,o6,o7,o8,o9,o10;
    
    if(!objectp(dagg))
        {
        dagg = clone_object(DAGGER);
        dagg->move(TO);
    }
    if (!objectp(o1))
        {
        o1=clone_object("/d/Kalad/common/wild/pass/dwarf/crypt/d1");
        o1->arm_me();
        o1->move(TO);
    }
    if (!objectp(o2))
        {
        o2=clone_object("/d/Kalad/common/wild/pass/dwarf/crypt/d1");
        o2->arm_me();
        o2->move(TO);
    }
    if (!objectp(o3))
        {
        o3=clone_object("/d/Kalad/common/wild/pass/dwarf/crypt/d1");
        o3->arm_me();
        o3->move(TO);
    }
    if (!objectp(o4))
        {
        o4=clone_object("/d/Kalad/common/wild/pass/dwarf/crypt/d1");
        o4->arm_me();
        o4->move(TO);
    }
    if (!objectp(o5))
        {
        o5=clone_object("/d/Kalad/common/wild/pass/dwarf/crypt/d1");
        o5->arm_me();
        o5->move(TO);
    }
    if (!objectp(o6))
        {
        o6=clone_object("/d/Kalad/common/wild/pass/dwarf/crypt/d1");
        o6->arm_me();
        o6->move(TO);
    }
    if (!objectp(o8))
        {
        o8=clone_object("/d/Kalad/common/wild/pass/dwarf/crypt/d2");
        o8->arm_me();
        o8->move(TO);
    }
    o8->team_join(o1);
    o8->team_join(o2);
    o8->team_join(o3);
    o8->team_join(o4);
    o8->team_join(o5);
    o8->team_join(o6);
    corpse_here = 1;
}

string
corpse()
{
    if (corpse_here)
        {
        return "you can see a large human corpse. What amazes you "+
        "is that it is almost not decayed at all. The man "+
        "wears an old, scarred platemail "+
        "and holds a shining waraxe in a tight grip "+
        "in its right hand. A large ring adorns the bony hands "+
        "middle finger. The gems on it shines brightly in your "+
        "eyes, making you believe it was it that created "+
        "the glimmer of light you saw. Then you notice something "+
        "wierd. There is a hole through the chest of the corpse, "+
        "just where the heart once was. It seems like he was "+
        "killed by someone tearing it out!";
    }
    return "you notice that it is empty...";
}

void
init()
{
    ::init();
    add_action("put_heart","place");
    add_action("put_heart","put");
    add_action("put_heart","insert");
}

int
put_heart(string str)
{
    int heart;
    int item_number;
    int i;
    object *obj;
    
    NF("Insert what into where?\n");
    if (!str) return 0;
    if (!parse_command(str,environment(TP), "'heart' [in] [inside] [into] 'chest' / 'hole' / 'corpse'"))
        notify_fail("You don't see that place here, so you cannot insert it.\n");
    if(!corpse_here) return 0;
    
    obj = all_inventory(TP);
    for (i=0;i<sizeof(obj);i++)
    {
        if(obj[i]->query_name() == "heart")
            {
            heart = 1;
            item_number = i;
         }
    }
    NF("Why do you want to place that into it? You decide against it.\n");
    if (!heart) return 0;
    
    TP->catch_msg("You place the heart inside the hole in the corpse. "+
        "Suddenly the hole closes!\n");
    
    if(obj[item_number]->query_prop("_korat_heart_type")==GHOUL)
        {
        tell_room(TO,"The sarcophagus starts to shake and cracks open! "+
            "The corpse becomes alive, but instead of two dead eyes you "+
            "now see two eyes staring at you with a promise of a dark and "+
            "cruel death...\n");
        kabal=clone_object(CPASS(dwarf/npc/kabal));
        kabal->arm_me();
        kabal->move_living("M",TO);
        tell_room(TO,"The decaying remains of a human "+
            "stares down at you and announces with "+
            "a voice as from the grave:\n\nYou gave me life, cruel life. "+
            "My first deed in this world shall be to destroy you who dared "+
            "to wake me from my sleep with the force of a ghouls heart!\n\n");
        kabal->command("emote walks slowly towards you with death in its eyes.");
        tell_room(TO,"An aura of death and decay seems to envelope you "+
            "slowly, as the decaying remains of a human gets closer and closer.\n");
        set_alarm(10.0,0.0,"kabal_attack",TP);
        corpse_here = 0;
        obj[item_number]->remove_object();
        return 1;
    }
    
    if(obj[item_number]->query_prop("_korat_heart_type")==GOOD)
        {
        tell_room(TO,"The sarcophagus starts to shake and cracks open! "+
            "The corpse suddenly animates, and a voice fills the room as "+
            "spoken from the grave: 'You have given me eternal rest. "+
            "Take my ring as a token of my gratitude.'\n");
        tell_room(TO,"The corpse releases a ring from its finger, and you pick "+
            "it up carefully. Suddenly the corpse crumbles to dust.\n");
        corpse_here = 0;
        obj[item_number]->remove_object();
        ring = clone_object("/d/Kalad/common/wild/pass/dwarf/arm/kabal_ring");
        ring -> move(TP);
        return 1;
    }
    tell_room(TO,"The corpse turns to dust with nothing left from it.\n");
    corpse_here = 0;
    obj[item_number]->remove_object();
    return 1;
}

void
kabal_attack(object player)
{
    kabal->command("emote announces: Prepare to die fool.");
    kabal->command("emote starts to reach out for you.");
    kabal->command("kill "+ player->query_real_name());
}
