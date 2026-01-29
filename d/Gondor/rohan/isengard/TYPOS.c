From the typo log:

Sep 30 1997 /d/Gondor/rohan/isengard/storerm1 (Gnadnar)
in "weapon rack", better not to end a sentence with a preposition, as in:
	A few swords and halberds have been placed in the racks for the guards to
	have immediate access to.
you could just make it:
	A few swords and halberds have been placed in the racks for the use
	the guards.
or something like that .. but it sounds clumsy as it is.

Sep 30 1997 /d/Gondor/rohan/isengard/storerm2 (Gnadnar)
in "floor" desc, "its hard" should be "it's hard"

Sep 30 1997 /d/Gondor/rohan/isengard/storerm2 (Gnadnar)
in "tobacco crates", "accessability" should be "accessibility"

Sep 30 1997 /d/Gondor/rohan/isengard/storerm2 (Gnadnar)
i'm not positive -- might check with gorboth -- but i think that
in the crates desc, the stenciled/marked words should be inside
quotation marks.  that is, instead of :
	These crates are stacked together against a wall and have the word food
	stenciled across the front and top.
do:
	These crates are stacked together against a wall and have the word "Food"
	stenciled across the front and top.
similarly,
	The crates have been clearly marked "Tobacco" on the front and top.
for tobacco crates.

Sep 30 1997 /d/Gondor/rohan/isengard/lookout1 (Gnadnar)
i think you may need a comma after "gate" in:
	Currently two dark-haired men, guarding the gate can be spotted
	on the pathway.
(when i exa pathway)

Sep 30 1997 /d/Gondor/rohan/isengard/wtower2 (Gnadnar)
in the room desc:
	one of the watch towers that tower above
"towers that tower" is awkward.  try "towers that rise above the gate", "towers
that shadow the gate", "towers that loom over the gate", .... but
not "towers that tower"
(same thing is true of "towers" item)

Sep 30 1997 /d/Gondor/rohan/isengard/wtower1 (Gnadnar)
in "dirt" desc, "stired up" should be "stirred up".

Sep 30 1997 /d/Gondor/rohan/isengard/wtower1 (Gnadnar)
the "floor" desc would read more smoothly if :
	There is a fine layer of dirt that is covering the floor.
were
	There is a fine layer of dirt covering the floor.


From the bug log:
Sep 30 1997 /d/Gondor/rohan/isengard/isengate (Gnadnar)
should be able to exa wall, walls, ring-wall, ring-walls

Sep 30 1997 /d/Gondor/rohan/isengard/isengate (Gnadnar)
should be able to exa hinges, doors (on gates)

Sep 30 1997 /d/Gondor/rohan/isengard/isengate (Gnadnar)
should be able to exa tower, towers, watch tower, watch towers.

Sep 30 1997 /d/Gondor/rohan/isengard/npc/dunlend#3905 (Gnadnar)
the desc says: ... He is tall, swarthy ... and then
He is short and fat for a human.
so are the guards tall? or not?

Sep 30 1997 /d/Gondor/rohan/isengard/tunnel3 (Gnadnar)
should be able to exa hand (on door).  might do hinges,
too, while you're at it.

Sep 30 1997 /d/Gondor/rohan/isengard/isengate (Gnadnar)
if the guards have been killed, then the room desc looks odd when 
it talks about "the guard outside the gates".  maybe use VBFC for that,
so you only talk about guards if they exist?

Sep 30 1997 /d/Gondor/rohan/isengard/guardrm (Gnadnar)
should be able to exa fire, hearth.

Sep 30 1997 /d/Gondor/rohan/isengard/guardrm (Gnadnar)
either the door should id to "doorway", or the room desc should
say "a door leads".   

Sep 30 1997 /d/Gondor/rohan/isengard/guardrm (Gnadnar)
should be able to exa dark room, dark rooms
(not that we necessarily could see much, since they're dark, but
some response other than "You find no dark room(s)." would be good.

Sep 30 1997 /d/Gondor/rohan/isengard/storerm1 (Gnadnar)
should be able to exa weapon racks  (singular works, but need plural too)

Sep 30 1997 /d/Gondor/rohan/isengard/storerm1 (Gnadnar)
should be able to exa armour, armours, weapon, weapons, sword, swords, halberd,
halberds (in racks).  also be nice to have some custom response to
attempts to take the armour/weapons from the racks.

Sep 30 1997 /d/Gondor/rohan/isengard/storerm1 (Gnadnar)
since you say "the walls are damp to the touch", really should
respond to attempts to "touch wall(s)".

Sep 30 1997 /d/Gondor/rohan/isengard/storerm1 (Gnadnar)
should be able to exa ceiling?

Sep 30 1997 /d/Gondor/rohan/isengard/storerm1 (Gnadnar)
same comments re exa and get/take apply to armour on hooks, as well
as in racks.

Sep 30 1997 /d/Gondor/rohan/isengard/stair1 (Gnadnar)
should be able to exa staircase, wall, walls, ceiling, opening, lookout

Sep 30 1997 /d/Gondor/rohan/isengard/lookout2 (Gnadnar)
should be able to exa window, glow, light (from tower)

Sep 30 1997 /d/Gondor/rohan/isengard/lookout2 (Gnadnar)
should be able to exa towers (the ones mentioned in the "lookout" desc).
i suppose you need to be able to distinguish between the guard towers
and the "tall, tower-like structure" in the distance?

Sep 30 1997 /d/Gondor/rohan/isengard/stair1 (Gnadnar)
the "down" exit here tries to put me in "storeroom1";
it should be "storerm1"

Sep 30 1997 /d/Gondor/rohan/isengard/npc/isen_guard#22229 (Gnadnar)
i see:
	Two brutal male humans, a ferocious male human, a foul male human and a
	deadly male human.
but "exa humans" fails.

Sep 30 1997 /d/Gondor/rohan/isengard/storerm2 (Gnadnar)
should be able to exa ceiling, equipment crates

Sep 30 1997 /d/Gondor/rohan/isengard/npc/isen_captain#10147 (Gnadnarjr)
should respond to being asked about head, trophy, ranger ....

Sep 30 1997 /d/Gondor/rohan/isengard/storerm2 (Gnadnar)
should be able to exa equipment crate

Sep 30 1997 /d/Gondor/rohan/isengard/lookout2 (Gnadnar)
should be able to exa spikes ?

Sep 30 1997 /d/Gondor/rohan/isengard/lookout3 (Gnadnar)
please consider using "down" for the exit direction, instead of "stairs".
"stairs" as a direction is clumsy, to my way of thinking. what's more,
lookout2 and the staircase leading to the storeroom used "up" and "down",
and it would be better to be consistent.

Sep 30 1997 /d/Gondor/rohan/isengard/lookout3 (Gnadnar)
i'm not going to repeat the comments that are the same from room to room 
(e.g., should be able to look at window in tower in all these top rooms)
so i won't utterly spam the buglog :-)

Sep 30 1997 /d/Gondor/rohan/isengard/lookout3 (Gnadnar)
should be able to exa staircase

Sep 30 1997 /d/Gondor/rohan/isengard/lookout3 (Gnadnar)
"stairs" exit fails to load /d/Gondor/rohan/isengard/ringrd3.c

Sep 30 1997 /d/Gondor/rohan/isengard/wtower2 (Gnadnar)
"opening" desc says "...the lookout to the east" but the lookout is west

Sep 30 1997 /d/Gondor/rohan/isengard//npc/archer#12783 (Gnadnar)
hmm .. the archers in the other tower had a short desc of
"dunlending archer"; this one just has "man".  i think "dunlending archer"
looks more interesting ...

