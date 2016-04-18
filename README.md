# cpp-collect-game
A "collecting coins" multiplayer game written in C++ using [Haafs Game Engine (HGE)](https://sourceforge.net/projects/hge/). This is a game a wrote in my first year at Blekinge Institute of Technology. 

### How to play
Your objective is to get more coins than your opponent. You can pick up additional artifacts in the game in order to get a advantage of your opponent. But beware! Some items might net negative effects ... randomly...

#### The Coin
![](https://raw.githubusercontent.com/devinant/cpp-collect-game/master/assets/textures/coin/spinning.png)

Collect the coins to increase your score, they increase your running speed for a short amount of time. Why? So you can collect even MORE coins!

#### Spinning Potion
![](https://raw.githubusercontent.com/devinant/cpp-collect-game/master/assets/textures/haste.png)

A magical potion that resembles a green whirlpool (don't ask). When collected, the running speed increases for a short amount of time. However, sometimes the potion is brewed improperly and when the hero picks it up he becomes slower!

#### Hourglass
![](https://raw.githubusercontent.com/devinant/cpp-collect-game/master/assets/textures/hourglass.png)

Warps spacetime itself and nets the hero more time to pick up even more coins! Sometimes, this hourglass is broken and the hero is transported to the future. It is said that a mysterious man in a DeLorean crafted this artifact.

#### The weight
![](https://raw.githubusercontent.com/devinant/cpp-collect-game/master/assets/textures/weight.png)

Fancy a workout? Looks may be deceiving! When the hero picks up the weight, he becomes bigger and can pick-up even more coins! Your movement speed decreases for a short amount of time. 
### Screenshots
![](https://raw.githubusercontent.com/devinant/cpp-collect-game/master/screenshot1.png)
![](https://raw.githubusercontent.com/devinant/cpp-collect-game/master/screenshot1.png)

### Compiling
You can compile the game in Visual Studio 2010, 2012 and 2015. If the compilation fails, do the following:

1. Open the solution
2. Right-click on the **Tin** project and select **Properties**
3. Navigate to **Configuration Properties** -> **General**
4. Set **Platform Toolset** to **Visual Studio 2010 (v100)** 
