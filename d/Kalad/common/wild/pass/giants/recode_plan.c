Hi.
113, 1 chief, 1 chiefwolf, 15 giants,48 wolves and 48 goblins total
vs. 132 guards in noble houses kabal (in rooms, and summoned by nobles)


//old bug report to cotillion about summoned goblins entering the room in battle with the giants. 23/6/2020-25/6/2020

I am thinking to set XP at 140, because....
Mobs have been compared to /d/Kalad/common/noble/npc/house_guard, they are the weakest from Kabal.
For a Hero - Tested with jr for around 90 battles against each group.

Kill speed is faster vs giant+summons than against 5 house_guards
house_guards = 40 secs pr mobs, total of 200
giant = 80 secs, goblins+wolves = 20, total of 200
When the last mob is killed, avg health against giants was bad shape
When the last mob is killed, avg health against house_guards was somewhat hurt.
I've set giants at xp130, goblins+wolves at xp120.
This gives equal xp to house_guards.

However, the battles are harder and players will take more damage.



/w/meton/open/giantrecode----
//1:mobs have had added a bit of stat.
//2:special and loot kill added.
//3:Changed to active_monster_base
//4:Ac is added in giants.
//5:wolves have trinketloots

My plan is to change giants in the following ways
//1:adding ac to giant.
//2:Adding gems/coins worth similar to guards loot level, since there isnt valuable loot - Increased loot to equal the summoned wolves, minus the trinket drops.
//3:Depending on AoB, adding more HP.
//4:To avoid making a huge area which i feel is wrong thematically, giants summon wolves to aid them. This makes it into a grindable area.
//The summon is randomized, thus favoring the true target players, as bigger players don't get as many summons.
//Summons limited to...3x2 pr giant.
    //-   Summon set to 1 wolf + 1 goblin raider pr
//5:Adding a room for pack-mother of wolves, perhaps make her as a boss-fight too. ---skipped so far
//6:Upgrade hgchiefs weapon. At 100 kg it will still be a joke to use, but currently i feel its just plain silly.
//7:Wolves drop pelts, random chance for a good pelt like hell-hounds from Kalaman - skipped, cause looks silly with trinkets. Only trinkets.
//8: Wolves drop random trinkets(from people they ate, armrings, rings, necklaces, shoulder things, boots)
//-- Only one corpse-drop type possible, to avoid silly syntax
//9:Adding a special to the giants.
//10: alignment set at -400 to mirror guards 400
//11: Adding looting players weapons, and using them




To balance xp(don't know how their bonus tool works, perhaps use add_temp_stat to take int/wis down to "wanted levels")

So, in order to gain status as grind area we need more
xp
loot
interest

1:Up xp by upping giants slightly.
    a:The skewed stats are show clearly if you're underpowered, but with equal power or OP, skewed stats give same xp as even stats.
    AC break point. Need to find the point where AC gives more, but doesn't overpower players.
    b:More mobs. Theme of giant village doesnt fit 30+ giants, so ideas are
        1:Summon wolves to aid(upping numbers)
        2:Increasing con, int/wis slightly(longer fight from con)
        3:Increasing hp from con(longer fight)
        4:summoning other fitting mobs
    c: Multiple rooms - Not very fitting.
2:Loot.
    a:If summon mobs, have mobs bring stuff
        1:Wolves with pelts
        2:others with regular loot
    b:If summon mobs, have mobs with no loot, and up loot on giants
    c:Make more armours on giants - Bad idea, i like giants to have heavy armours so bad for loot.
    d:Gems - 
    e:trinkets - More rings/earrings/shoulderitems/belts/boots etc etc.

3: Interest- 
    a:This means something to find here.
    b:Up items, so there are higher chance for imbues.
    c:Get some gear people want/can use.
