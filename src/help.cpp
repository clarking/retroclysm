#include "game.h"
#include "keypress.h"

#ifndef LINE_XOXO
	#define LINE_XOXO 4194424
	#define LINE_OXOX 4194417
	#define LINE_XXOO 4194413
	#define LINE_OXXO 4194412
	#define LINE_OOXX 4194411
	#define LINE_XOOX 4194410
	#define LINE_XXXO 4194420
	#define LINE_XXOX 4194422
	#define LINE_XOXX 4194421
	#define LINE_OXXX 4194423
	#define LINE_XXXX 4194414
#endif

void game::help() {
	char ch;
	do {
		erase();
		mvprintz(0, 38, c_red, "HELP");
		mvprintz(1, 0, c_white, "\
Please press one of the following for\n\
help on that topic:\n\
\n\
a: Introduction\n\
b: Movement\n\
c: Hunger, Thirst, and Sleep\n\
d: Pain and Stimulatants\n\
e: Addiction\n\
f: Morale\n\
g: Radioactivity and Mutation\n\
h: Bionics\n\
i: Crafting\n\
j: Items overview\n\
k: Combat\n\
l: Survival tips\n\
\n\
1: List of all commands\n\
2: List of item types and data\n\
3: Description of map symbols\n\
\n\
q: Return to game");

		ch = getch();
		switch (ch) {
			case 'a':
			case 'A':
				erase();
				mvprintz(0, 0, c_white, "\
RetroClysm is a roguelike with a monster apocalypse setting. You have survived\n\
the original onslaught, and are ready to set out in search of safety.\n\
\n\
RetroClysm differs from most roguelikes in several ways. Rather than exploring\n\
an underground dungeon, with a limited area on each level, you are exploring\n\
a truly infinite world, stretching in all four cardinal directions.\n\
As in most roguelikes, you will have to find food; you also need to keep\n\
yourself hydrated, and sleep periodically.\n\
\n\
While RetroClysm has more challenges than many roguelikes, the near-future\n\
setting makes some tasks easier. Firearms, medications, and a wide variety of\n\
tools are all available to help you survive.");
				getch();
				break;

			case 'b':
			case 'B':
				erase();
				mvprintz(0, 0, c_white, "\
Movement is performed using the numpad, or vikeys. Each step will take 100\n\
                    movement points (or more, depending on the terrain); you\n\
y  k  u   7  8  9   will then replenish a variable amount of movement points,\n\
 \\ | /     \\ | /    depending on many factors (press '@' to see the exact\n\
  \\|/       \\|/     amount). To attempt to hit a monster with your weapon,\n\
h--.--l   4--5--6   simply move into it. You may find doors, ('+'); these may\n\
  /|\\       /|\\     be opened with 'o' or closed with 'c'. Some doors are\n\
 / | \\     / | \\    locked. Locked doors, windows, and some other obstacles\n\
b  j  n   1  2  3   can be destroyed by smashing them ('s', then choose a\n\
                    direction). Smashing down obstacles is much easier with a\n\
good weapon or a strong character.\n\
\n\
There may be times when you want to move more quickly by holding down a\n\
movement key. However, fast movement in this fashion may lead to the player\n\
getting into a dangerous situation or even killed before they have a chance\n\
to react. Pressing '!' will toggle \"Run Mode.\" While this is on, any\n\
movement will be ignored if new monsters enter the player's view.");
				getch();
				break;

			case 'c':
			case 'C':
				erase();
				mvprintz(0, 0, c_white, "\
As time passes, you will begin to feel hunger and thirst.  A status warning\n\
at the bottom of the screen will appear.  As hunger and thirst reach critical\n\
levels, you will begin to suffer movement penalties. Thirst is more dangerous\n\
than hunger.  Finding food in a city is usually easy; outside of a city, you\n\
may have to hunt an animal, then stand over its corpse and 'B'utcher it into\n\
small chunks of meat. Likewise, outside of a city you may have to drink water\n\
from a river or other natural source; stand in shallow water and press 'g' or\n\
',' to pick it up.  You'll need a watertight container.\n\
\n\
Every 14 to 20 hours, you'll find yourself growing sleepy.  If you do not\n\
sleep by pressing '$', you'll start suffering stat and movement penalties.\n\
You may not always fall asleep right away.  Sleeping indoors, especially on a\n\
bed, will help; or you can always use sleeping pills.  While sleeping, you'll\n\
slowly replenish lost hit points.  You'll also be vulnerable to attack, so\n\
try to find a safe place, or set traps for unwary intruders.");
				getch();
				break;

			case 'd':
			case 'D':
				erase();
				mvprintz(0, 0, c_white, "\
When you take damage from almost any source, you'll start to feel pain.  Pain\n\
slows you down and reduces your stats, and finding a way to manage pain is an\n\
early imperative.  The most common is drugs; aspirin, codeine, tramadol,\n\
oxycodone, and more are all great options.  Be aware that while under the\n\
influence of a lot of painkillers, the physiological effects may slow you or\n\
reduce your stats.\n\
\n\
Pain will also disappear with time, so if drugs aren't available and you're\n\
in a lot of pain, it may be wise to find a safe spot and simply rest for an\n\
extended period of time.");
				getch();
				break;

			case 'e':
			case 'E':
				erase();
				mvprintz(0, 0, c_white, "\
Many drugs have a potential for addiction.  Each time you consume such a drug\n\
there is a chance that you will grow dependant on it.  Consuming more of that\n\
drug will increase your dependance.  Effects vary greatly between drugs, but\n\
all addictions have only one cure; going cold turkey.  The process may last\n\
days, and will leave you very weak, so try to do it in a safe area.\n\
\n\
If you are suffering from drug withdrawal, taking more of the drug will cause\n\
the effects to cease immediately, but may deepen your dependance.");
				getch();
				break;

			case 'f':
			case 'F':
				erase();
				mvprintz(0, 0, c_white, "\
Your character has a morale level, which affects you in many ways.  The\n\
depressing post-apocalypse world is tough to deal with, and your mood will\n\
naturally decrease very slowly.\n\
\n\
There are lots of options for increasing morale; reading an entertaining\n\
book, eating delicious food, and taking recreational drugs are but a few\n\
options.  Most morale-boosting activities can only take you to a certain\n\
level before they grow boring.\n\
\n\
There are also lots of ways for your morale to decrease, beyond its natural\n\
decay.  Eating disgusting food, reading a boring technical book, or going\n\
through drug withdrawal are some prominent examples.\n\
\n\
Low morale will make you sluggish and unmotivated.  It will also reduce your\n\
stats, particularly intelligence.  If your morale drops very low, you may\n\
even commit suicide.  Very high morale fills you with gusto and energy, and\n\
you will find yourself moving faster.  At extremely high levels, you will\n\
receive stat bonuses.");
				getch();
				break;

			case 'g':
			case 'G':
				erase();
				mvprintz(0, 0, c_white, "\
Though it is relatively rare, certain areas of the world may be contamiated\n\
with radiation.  It will gradually accumulate in your body, weakening you\n\
more and more.  While in radiation-free areas, your radiation level will\n\
slowly decrease.  Taking iodine tablets will help speed the process.\n\
\n\
If you become very irradiated, you may develop mutations.  Most of the time,\n\
these mutations will be negative; however, many are beneficial, and others\n\
have both positive and negative effects.  Your mutations may change your play\n\
style considerably.  They are extremely rare, but it is possible to find\n\
substances that will remove mutations.");
				getch();
				break;

			case 'h':
			case 'H':
				erase();
				mvprintz(0, 0, c_white, "\
Bionics are biomechanical upgrades to your body.  While many are simply\n\
'built-in' versions of items you would otherwise have to carry, some bionics\n\
have unique effects that are otherwise unobtainable.\n\
\n\
Most bionics require a source of power, and you will need an internal battery\n\
to store energy for them.  Your current amount of energy is displayed below\n\
your health.  Replenishing energy can be done in a variety of ways, but all\n\
require the installation of a special bionic just for fuel consumption.\n\
\n\
Bionics come in ready-to-install canisters, most of which contain supplies\n\
for several different modules.  Installing a bionic will consume the entire\n\
canister, so choose your upgrade carefully.  Installation of a bionic is best\n\
left to a trained professional; however, you may attempt to perform a self-\n\
installation.  Performing such a task requires high levels of surgery,\n\
mechanics, and/or electrions, and failure may cripple you!  Bionics canisters\n\
are difficult to find, but they may be purchased from certain NPCs for a very\n\
high price.");
				getch();
				break;

			case 'i':
			case 'I':
				erase();
				mvprintz(0, 0, c_white, "\
Many important items can be very hard to find, or will cost a great deal of\n\
money to trade for.  Fortunately, it is possible to craft a wide variety of\n\
goods with the proper tools, materials, and training.\n\
\n\
Some recipes require a set of tools.  These are not used up when crafting, so\n\
you can keep your tool set.  All recipes require one or more ingredients.\n\
These ARE used up in crafting.\n\
\n\
To craft items, press '&'.  There are five categories; Weapons, Food,\n\
Electronics, Armor, and Miscellaneous.  While a few items require no skill to\n\
create, the majority require you to have some knowledge:\n\
\n\
->Mechanic skill is used for weapons, traps, and a few tools.\n\
->Cooking skill, at low levels, is used for making tasty recipes; at higher\n\
levels, you have an understanding of chemistry and can make chemical weapons\n\
and beneficial elixirs.\n\
->Electronics skill lets you make a wide variety of tools with intricate uses.\n\
->Tailoring skill is used to create basic clothing, and later tough armor.\n\
\n\
In addition to the primary crafting skills, other skills may be necessary to\n\
create certain items.  Traps skill, Firearms skill, and First Aid skill are\n\
all required for certain items.");
				getch();
				break;

			case 'j':
			case 'J':
				erase();
				mvprintz(0, 0, c_white, "\
There are a wide variety of items available for your use. You may find them\n\
lying on the ground; if so, simply press ',' or 'g' to pick up items on the\n\
same square. Some items are found inside a container, drawn as a { with a\n\
blue background. Pressing 'e', then a direction, will allow you to examine\n\
these containers and loot their contents.\n\
\n\
All items may be used as a melee weapon, though some are better than others.\n\
You can check the melee attributes of an item you're carrying by hitting 'i'\n\
to enter your inventory, then pressing the letter of the item.  There are 3\n\
values, displayed as (B#/C#/H#). B indicates the bashing damage dealt, C is\n\
cutting damage, and H is a bonus (or penalty) to your chance to hit.\n\
Bashing damage is universally effective, but is capped by low strength.\n\
Cutting damage is a guaranteed increase in damage, but it may be reduced by\n\
a monster's natural armor.\n\
\n\
To wield an item as a weapon, press 'w' then the proper letter.  Pressing '-'\n\
in lieu of a letter will make you wield nothing.  A wielded weapon will not\n\
contribute to your volume carried, so holding a large item in your hands may\n\
be a good option for travel.  When unwielding your weapon, it will go back in\n\
your inventory, or will be dropped on the ground if there is no space.\n\
\n\
To wear a piece of clothing, press 'W' then the proper letter.  Armor reduces\n\
damage and helps you resist things like smoke.  To take off an item, press\n\
'T' then the proper letter.");
				getch();
				break;
			case 'k':
			case 'K':
				erase();
				mvprintz(0, 0, c_white, "\
After 30 minutes of warmup time, monsters will begin to appear. They are\n\
represented by letters on your screen; a list of monster names, and their\n\
positions relative to you, is displayed on the right side of the screen.\n\
\n\
To attack a monster with a melee weapon, simply move into them. The time it\n\
takes to attack depends on the size and weight of your weapon.  Small, light\n\
weapons are the fastest; unarmed attacks increase in speed with your Unarmed\n\
Combat skill, and will eventually be VERY fast.  A successful hit will stun\n\
the monster temporarily, and most one-on-one fights will be easily won by the\n\
player.  On the other hand, a miss will make you stumble and cost YOU\n\
movement points.\n\
\n\
Swarms of monsters may call for firearms. If you find one, wield it first,\n\
then reload by pressing 'r'. If you wish to change ammo, you must unload the\n\
weapon by pressing 'U', then reload again. To fire, press 'f', move the\n\
cursor to the relevant space, then hit '.' or 'f'. Some guns have automatic\n\
fire; to shoot a burst, press 'F'. This will severely reduce accuracy.  If\n\
you are hit, your clothing will absorb some damage, but you will suffer\n\
the excess.\n\
\n\
Unlike most roguelikes, fleeing will often be your best option, especially\n\
when overwhelmed by a swarm of zombies.  Try to avoid getting cornered inside\n\
a building.  Ducking down into the subways or sewers is often an excellent\n\
escape tactic.");
				getch();
				break;

				getch();
				break;
			case 'l':
			case 'L':
				erase();
				mvprintz(0, 0, c_white, "\
The first thing to do is to check your home for useful items. Your initial\n\
storage is limited, and a backpack, trenchcoat, or other storage medium will\n\
let you carry a lot more. Finding a weapon is important; frying pans, butcher\n\
knives, and more are common in your home; hardware stores may carry others.\n\
Unless you plan on concentrating on melee combat, seek out gun stores as soon\n\
as possible and load up on more than one type.\n\
\n\
It's also important to carry a few medications; painkillers are a must-have,\n\
and drugs such as cigarettes will make life easier (but beware addiction).\n\
Leave cities as soon as you have a good stockpile of equipment. Their high\n\
concentration of zombies makes them a deathtrap--but a necessary resource for\n\
food and ammunition.\n\
\n\
Combat is much easier if you can fight just one monster at once. Use doorways\n\
as a choke Point, or stand behind a window and strike as the zombies slowly\n\
climb through. Never be afraid to just run if you can outpace your enemies.\n\
Irregular terrain, like forests, may help you lose monsters.\n\
\n\
Firearms are the easiest way to kill an enemy, but the sound will attract\n\
unwanted attention. Save the guns for emergencies, and melee when you can.\n\
\n\
Try to keep your inventory as full as possible without being overloaded.  You\n\
never know when you might need an item, and most are good to sell, and you\n\
can easily drop unwanted items on the floor.");
				getch();
				break;

			case '1':
				erase();
				mvprintz(0, 0, c_white, "MOVEMENT:");
				mvprintz(1, 0, c_ltgray, "\
vikeys or numpad - Movement or attack        . or 5 - Pause for one turn\n\
o - Open a door                              c      - Close a door\n\
s - Smash terrain                            , or g - Pick up items\n\
e - Examine terrain, open container          < or > - Go up or down stairs\n\
$ - Lie down to sleep                        ^      - Long wait\n\
! - Toggle Run Mode");
				mvprintz(7, 0, c_white, "ITEMS:");
				mvprintz(8, 0, c_ltgray, "\
i - View Inventory                           d - Drop item\n\
w - Wield item                               t - Throw item\n\
W - Wear item                                T - Take off item\n\
a - Activate tool                            E - Eat comestible\n\
r - Reload wielded gun or tool               U - Unload wielded gun or tool\n\
f - Fire gun                                 F - Burst-fire gun\n\
p - Power up / List bionics                  R - Read book\n\
& - Craft items                              B - Butcher a corpse");
				mvprintz(16, 0, c_white, "INFORMATION:");
				mvprintz(17, 0, c_ltgray, "\
@ - View character status                    # - List factions\n\
: - Open world map                           ; - Look around\n\
C - Chat with NPC                            ? - Help page\n\
% - View kill counts");
				mvprintz(21, 0, c_white, "META:");
				mvprintz(22, 0, c_ltgray, "\
S - Save game                                Q - Quit w/o saving");
				mvprintz(23, 0, c_red, "\
Note that 'a' is context-sensitive, and can be used in place of 'W', 'E', or\n\
'R', if you like.");
				getch();
				break;
			case '2':
				erase();
				mvprintz(0, 0, c_white, "\
ITEM TYPES:\n\
~       Liquid\n\
%%%%       Food\n\
!       Medication\n\
    These are all consumed by using 'E'. They provide a certain amount of\n\
 nutrition, quench your thirst, may be a stimulant or a depressant, and may\n\
 provide morale. There may also be more subtle effects.\n\
\n\
/       Large weapon\n\
;       Small weapon or tool\n\
,       Tiny item\n\
    These are all generic items, useful only to be wielded as a weapon.\n\
 However, some have special uses; they will show up under the TOOLS section\n\
 in your inventory. Press 'a' to use these.\n\
\n\
)       Container\n\
    These items may hold other items. Someare passable weapons. Many will be\n\
 listed with their contents, e.g. \"plastic bottle of water\". Those containing\n\
 comestibles may be eaten with 'E'; this may leave you with an empty container.\n\
Press any key to continue...");
				getch();
				clear();
				mvprintz(0, 0, c_white, "\
ITEM TYPES:\n\
[       Clothing\n\
    This may be worn with the 'W' key or removed with the 'T' key. It may\n\
 cover one or more body parts; you can wear multiple articles of clothing on\n\
 any given body part, but this will encumber you severely. Each article of\n\
 clothing may provide storage space, warmth, an encumberment, and a resistance\n\
 to bashing and/or cutting attacks. Some may protect against environmental\n\
 effects.\n\
\n\
(       Firearm\n\
    This weapon may be loaded with ammunition with 'r', unloaded with 'U', and\n\
 fired with 'f'. Some have automatic fire, which may be used with 'F' at a\n\
 penalty to accuracy. The color refers to the type; handguns are gray, shotguns\n\
 are red, submachine guns are cyan, rifles are brown, assault rifles are blue,\n\
 and heavy machine guns are green. Each has an accuracy rating, a bonus to\n\
 damage, a rate of fire, and a maximum load. Note that most firearms load\n\
 fully in one action, while shotguns must be loaded one shell at a time.\n\
\n\
=       Ammunition\n\
    Ammunition is worthless without a gun to load it into. Generally, there\n\
 are several variants for any particular calibre. Ammunition has a damage\n\
 rating, an accuracy, a range, and an armor-piercing quality.\n\
Press any key to continue...");
				getch();
				erase();
				mvprintz(0, 0, c_white, "\
ITEM TYPES:\n\
\n\
*       Thrown weapon; simple projectile or grenade\n\
    These items are suited for throwing, and many are only useful when\n\
 thrown, such as grenades, molotov cocktails, or tear gas.\n\
\n\
+       Book or magazine\n\
    This can be read for training or entertainment by pressing 'R'. Most\n\
 require a basic level of intelligence; some require some base knowledge in\n\
 the relevant subject.");
				getch();
				erase();
				break;
			case '3':
				erase();
				mvprintz(0, 0, c_ltgray, "MAP SYMBOLS:");
				mvprintz(1, 0, c_brown, "\
.           Field - Empty grassland, occasional wild fruit.");
				mvprintz(2, 0, c_green, "\
F           Forest - May be dense or sparse.  Slow moving; foragable food.");
				mvprintz(3, 0, c_dkgray, "\
%c%c%c%c%c%c%c%c%c%c%c Road - Safe from burrowing animals.", LINE_XOXO,
						 LINE_OXOX, LINE_XXOO, LINE_OXXO, LINE_OOXX, LINE_XOOX, LINE_XXXO,
						 LINE_XXOX, LINE_XOXX, LINE_OXXX, LINE_XXXX);
				mvprintz(4, 0, c_dkgray, "\
H=          Highway - Like roads, but lined with guard rails.");
				mvprintz(5, 0, c_dkgray, "\
|-          Bridge - Helps you cross rivers.");
				mvprintz(6, 0, c_blue, "\
R           River - Most creatures can not swim across them, but you may.");
				mvprintz(7, 0, c_dkgray, "\
O           Parking lot - Empty lot, few items.  Mostly useless.");
				mvprintz(8, 0, c_ltgreen, "\
^>v<        House - Filled with a variety of items.  Good place to sleep.");
				mvprintz(9, 0, c_ltblue, "\
^>v<        Gas station - Good place to collect gasoline.  Risk of explosion.");
				mvprintz(10, 0, c_ltred, "\
^>v<        Pharmacy - The best source for vital medications.");
				mvprintz(11, 0, c_green, "\
^>v<        Grocery store - Good source of canned food and other supplies.");
				mvprintz(12, 0, c_cyan, "\
^>v<        Hardware store - Home to tools, melee weapons and crafting goods.");
				mvprintz(13, 0, c_ltcyan, "\
^>v<        Sporting Goods store - Several survival tools and melee weapons.");
				mvprintz(14, 0, c_magenta, "\
^>v<        Liquor store - Alcohol is good for crafting molotov cocktails.");
				mvprintz(15, 0, c_red, "\
^>v<        Gun store - Firearms and ammunition are very valuable.");
				mvprintz(16, 0, c_blue, "\
^>v<        Clothing store - High-capacity clothing, some light armor.");
				mvprintz(17, 0, c_brown, "\
^>v<        Library - Home to books, both entertaining and informative.");
				mvprintz(18, 0, c_white, "\
^>v< are always man-made buildings.  The pointed side indicates the front door."
				);
				mvprintw(22, 0, "There are many others out there... search for them!");
				getch();
				erase();
				break;
		}
	} while (ch != 'q' && ch != KEY_ESCAPE);
}
