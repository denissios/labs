// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "menu.hpp"
#include "util.hpp"

#pragma comment(lib, "lib/DiceGroup.lib")

using opt_t = void (*)(DiceGroup&);

static constexpr std::string_view FORECAST[]
{
	"The stars of the horoscope, if they incline you to something, it is to laziness and increased sleepiness. A sleepy state can haunt him until the evening. If you don't find the strength to cheer up and tune in to activity, the day will pass without bringing anything special. Try drinking an extra cup of strong coffee in the morning. Well, if it doesn't help, there's nothing you can do about it!",
	"Any communication with the authorities is categorically contraindicated for you. If the bosses, as luck would have it, decide to call you �on the carpet�, hold some kind of conversation or talk to you on the phone, come up with any excuse. Anything: a sick grandmother, a sudden migraine, an atomic war ... Otherwise, on Tuesday, communication with the bosses in Taurus can smoothly flow into a conversation in a raised voice, and then into dismissal.",
	"Not only a great strategist will wake up in you, but also a great tactician. Do not even think to dissuade him from any ideas - you will only make trouble. Everything that you have planned on Wednesday, he will strive to implement in any way possible for him (including walking over his head). And listening to other people's objections on this day is not part of his plans.",
	"It is best for you to devote your free time to doing some kind of fitness or sports: such events promise to be held with benefits not only for the body, but also for the soul. In addition, it is in gyms on Thursday that meetings are very likely that can turn out to be an interesting and promising acquaintance for Taurus. Well, the fact that such exercises are useful for the figure is by itself.",
	"The best solution for you is to do something intellectually useful. At least that�s what you�ll do best. Yes, and there will be a lot of pleasure from such activities on Friday. If you are too lazy to solve problems or read smart books, you can just go to a museum, take some excursion, or at least wander around Wikipedia.",
	"Throughout the day, you will feel the urge to deal with all the pressing, as well as emerging issues and problems. The main thing is that this craving does not accidentally spread to a showdown with someone. It is much better to use it to put in order the accumulated cases. At the same time, it's good for you to clean up your purse or in your desk drawer - there on Saturday you can find what was considered irretrievably lost.",
	"Romance for you in the most wonderful way will coexist with practicality and prudence. In whatever clouds Taurus hovers on Sunday, somewhere in the depths of his brain there will be an attentive accountant with large clerical bills. This accountant will not allow the dreaming Taurus to do big stupid things.",
	"Your day will pass without any special events and shocks. Current affairs will not cause enthusiasm, and of all the entertainment, he will prefer to have fun at home, lying on his favorite couch. As for household chores (including urgent ones), you will want to postpone them for some time. And in vain, because these things would not take too much of his strength.",
	"More than ever, you can surprise everyone (including yourself) with your organizational skills. What you would have had to persuade others for a long time yesterday, you can do it without any extra effort. The gift of persuasion that awakens in you will be supported by the brightness of positive emotions combined with impeccable logic. It will not be easy for others to resist against such an arsenal!",
	"You may feel some dissatisfaction with your status. However, this discontent will not be acute. It's just that over and over again you may have a desire to strengthen and improve your image in the eyes of others. On this day, you will really have a chance to better establish yourself in the eyes of your superiors. Well, in the eyes of the opposite sex, there will also be an opportunity to present yourself in a favorable light.",
	"You will act with renewed vigor and determination! Perhaps he will not shine with great organizational talents, nevertheless, you have every chance to motivate others to do some useful and important business. At the same time, you can take matters too seriously, and his sense of humor will clearly not be up to par. Well, good! Seriousness is also sometimes needed.",
	"You may feel an inexplicable love of mathematics in yourself. Tasks that would have seemed boring and yawning on another day would not only be easier to solve, but would also be intellectually enjoyable. Perhaps you are not gaining the glory of a great mathematician, but doing something mentally useful clearly does not hurt! At least at the level of solving a crossword puzzle.",
	"You better not make important, responsible decisions. The stars of the horoscope every now and then will persuade him to take unnecessarily radical measures, and this is not always good. That is why it is useful for you to think it over once again before expressing your opinion and even more so starting to act. However, if a situation is ripe for a long time and requires drastic measures, this is a great day to take the bull by the horns!",
	"You will wake up an active theorist, but he will not be able to wake up the practice. All day you risk to spend in endless reflections on what, how and in what order he should do. These thoughts will be many, and they will all be surprisingly good. The only pity is that it is unlikely that any of these ideas will be implemented.",
	"Your day promises to be interesting and with considerable benefit! If you do not sit idly by, you can do so many things that you will only be surprised. Even the unusual restlessness that grips her on this day will not be able to stop her. It will manifest itself only in the fact that you will be able to bring any business to the end faster than usual, in order to immediately take on a new one.",
	"Your motto may well be the words: 'The most important thing is order in the house!' And this applies not only to cleaning the premises, but also to order in personal affairs. This is a great time for you to strengthen relationships with loved ones or eliminate misunderstandings that may have accumulated in the family at this moment. Well, home improvement will not hurt you either.",
	"Your maternal (well, or paternal) instinct may well become aggravated. It is not surprising if during the day you will repeatedly think about procreation and strengthening relationships with your loved one. On this day, you have a chance to bring your relationship to a new level: make a decision about whether to start a family or have a child. Well, if you just want to please yourself, you can bring a kitten or a hamster into the house.",
	"Self-confidence and self-confidence can literally overwhelm you! This feeling can reach such enormous proportions that it is possible that you will want to show nobility by providing someone with patronage and support. But if you succumb to noble impulses, you should not count on reciprocal gratitude - it may not be there.",
	"If you have a desire to strengthen your position and improve your image in the eyes of others (including in the eyes of the opposite sex), then this is most easily achieved by turning to the heights of philosophy. Try to show off your erudition in conversation. You can, for example, surprise those around you with a successful quote from Coelho or Kant, or even better - from some little-known but pretentious philosopher (rummage through Wikipedia).",
	"You may be surprised to find in yourself a penchant for Puritanism. On this day, her views on the rules of decency can be pretty hypertrophied. Ambiguous jokes and rude innuendos (it doesn't matter to whom they are directed) will irritate you and want to fight back immediately. So it won't take long to quarrel!",
	"You will try all day to control yourself, not reacting to annoying misunderstandings. There will be a lot of misunderstandings. Others, as luck would have it, will behave illogically and inconsistently. The funny thing is that Virgo will most likely be able to show restraint. But the tension in the soul will remain and literally in a day or two it can break through in some quarrel. So maybe you don't need to accumulate tension, but just dot all the i's?"
};

static constexpr opt_t OPTS[]
{
	[](DiceGroup& Dice) { Dice.roll(); },
	[](DiceGroup& Dice) { std::cout << "Forecast: " << FORECAST[Dice.getSum() % _countof(FORECAST)] << std::endl << std::endl; },
	[](DiceGroup& Dice) { std::cout << "Forecast: " << FORECAST[Dice.getSum() % _countof(FORECAST)] << std::endl << std::endl; },
	[](DiceGroup& Dice) { Dice += 1; },
	[](DiceGroup& Dice) { Dice -= 1; },
	[](DiceGroup& Dice) { std::cout << "Dice count: " << Dice.getSize() << std::endl << std::endl; }
};

static constexpr std::string_view MENU_MSGS[]
{
	"Exit",
	"Roll the dice",
	"Get forecast for today",
	"Get forecast for tomorrow",
	"Add dice",
	"Delete dice",
	"Get dice count"
};

inline static constexpr size_t OPTS_NUM{ _countof(OPTS) };
inline static constexpr size_t MENU_MSGS_NUM{ _countof(MENU_MSGS) };

static_assert(OPTS_NUM + 1 == MENU_MSGS_NUM, "Options size + 1 must be equal to msgs size"); // +1 for exit

void dialog(DiceGroup& Dice)
{
	while (true) {
		menu();

		auto choice = GetNumber<uint16_t>("Your choice: ");
		std::cout << std::endl;

		if (!choice)
			break;
		else if (choice > OPTS_NUM)
			std::cerr << "[WARNING] Wrong option\n\n";
		else
			OPTS[choice - 1](Dice);
	}
}

void menu()
{
	for (size_t i{}; i < MENU_MSGS_NUM; ++i)
		std::cout << i << ". " << MENU_MSGS[i] << std::endl;
}