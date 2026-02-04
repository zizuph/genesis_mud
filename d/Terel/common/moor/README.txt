NOTE: This area will go live on Feb 6, 2022 after Armageddon.
Benton is inaccessible until AoB gives ok on him and his goodies. 
See the file /tomb/gore_chamber.c to activate Benton when the 
approval comes through.

The files in /d/Terel/common/moor/* have been migrated from
/d/Terel/sorgum/* 

I will clean up the /moor dir once things open, as there are a lot of 
files just dumped into it w/o organization that I've moved to the
proper directories.

I have tried to bring the files up to current code standards
and resolve any bugs, typos, etc.

I've also located an unfinished quest involving a safe downstairs
in the cottage and have got it working. It uses GROUP,BIT 1,17 and
I've called it the Cottage Chest Quest. The main object for the 
quest is /d/Terel/common/moor/obj/flower_pot.c

I've added some more ancients/mystics flavor/mysteries, including
a new "ring of the ancients" which will help evade the stings
of the Wasp weapon.  I'm going to try to tie the ring and the Book 
of Darkness from the /d/Terel/mountain/ dir to the altar at the top
of the mountain, and bring the warlock (Vercus) into it, too. Still 
working that out.

As for the tomb, tomb dwellers, and Benton: I've left the ambiance
intact. I removed a chat or two from Benton that were a little
over the top. Shortened the paralyze, made it so he no longer drains
experience, and tried to make his spell attacks comply to current
magic standards. He now has native AC of 45, so with armour he's
in the range of 85-125 AC.

Zizuph helped fix the buggy arm-breaking code and got the doctor in 
Last updated. Fee to fix arms is 25 plats. Also, noticed that the  
doctor in Last has an ability to tell people who last scried them. 
Fee was 2plat and its now 5pc. I also added healing players of the 
plague for 10pc. 

I updated the Tanto weapon, putting it back into compliance with 
Balance standards. It has an alignment-based special attack. I also
created another knife I have called Wasp.  It does a stinging wound
that causes a non-additive attack delay. These items have been moved
to the /d/Terel/unique/* dir 

Maps:
I added to the corner_stone.txt file in the MAP_FILEs dir so that 
the new rooms in the cottage show up (the cellar, the toolshed, the
flower bed, and the forest), as well as new maps for the forest dir.

The old vamp guild connects to this area, so included the gate to
it in the maps. I also updated some exit directions in the avalanche
rooms in the old vamp guild so that when you climb the avalanche and
end up in the goblincaves it makes more sense on the maps.

I added a map file tombdweller.txt to the MAP_FILES dir  for that
area.

I haven't looked at/touched the trolls/troll area. I'm hoping I don't
need to.

Overall, I have tried to keep the original feeling of the tomb
and the little cottage. I remember when Sorgum made the 
cottage and how happy he was with it. He wanted to live in a 
place like it some day.


Lilith, Jan 2022

Done:
Updated exits on these rooms when it is time to open the area:
main/moor1 connects to /d/Terel/common/road/road5 
main/moor5 connects to /d/Terel/common/swamp/sw2
main/moor_path to /d/Terel/common/road/road10
forest/forest07 connects to /d/Terel/guilds/vamp/room/gate_outside
troll cave entrance will need to be uploaded as well.

PS
tomb03 ready to clone book_of_darkness when that is worked out.


