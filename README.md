# Particle Swarm Optimization

Implemention Of Particle Swarm Optimization Algorithm in C++ With Simple Environment

#### PSO

particle swarm optimization (PSO) is a metaheuristic optimization algorithm
it optimizes a problem by iteratively trying to improve a candidate solution
with regard to a given measure of quality.

#### Environment

our environment is a simple image and generate a random goal (Green Circle)
then with pso we can predict that.

## Dependencies

```bash
sudo apt install libopencv-dev
```
## How To Use ?
in your main file, include pso header and write your fitness function
then set instance of pso and set your parameters. then call optimize 
function and pass the fitness function in optimize parameter . EASY :)<br />
Recommended : Delete environment for your tasks

```javascript
#include "PSO.h"

auto fitnessfunction()
{}

auto main() -> int
{
 PSO pso;

 pso.set_c1(0.2);
 pso.set_c2(1.8);

 auto result = pso.optimize(fitnessfunction);
}
```

## Compilation

```bash
make
./pso
```

## Clean

```bash
make clean
```

## Environment Visualizer

<p align="center">
<img src = "https://github.com/ErfanFathi/pso/blob/master/Utils/::O.gif"</img>
</p>

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

## Finale

Feel free to use, modify or re-publish this code. And please feel free to fork the code 
from Github and send pull requests.

Report any comment or bugs to:<br />
fathierfan97@gmail.com<br />

Regards,<br />
Erfan Fathi<br />

