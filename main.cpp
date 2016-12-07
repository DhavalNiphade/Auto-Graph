/**
 * \class DAG
 * \file DAG.h
 *
 * \brief Provide a class for a Directed Acyclic Graph (DAG)
 *
 * This class provides the data structures and methods for a DAG
 * that can be used to store an Attribute-Value Matrix.
 *
 * \author Dhaval Niphade
 *
 * \version 1.0
 *
 * \date 2016/11/23 12:16:00 PM
 *
 * \date Created on: Wed Nov 20 12:16:00 2016
 *
 * \copyright Copyright 2016 by Dhaval Niphade
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.}
 *
 * \note This needs some more specification specification and optimization.
 *
 * \bug None
 */

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include <fstream>
#include <utility>
#include "DAG.h"
#include "Flow.h"
#include "SymbolMapper.h"
#include "PathMapper.h"

using namespace std;

void test() {

    //SymbolMapper sm;
    DAG myDAG1, myDAG2, myDAG3;
    SymbolMapper symbolStore;

    unsigned int to;

    // add first edge ROOT -AGR-> X
    to = myDAG1.addEdge(myDAG1.rootNodeId, symbolStore.getID("AGR"));
    // add edge to AGR target NUM=PL
    to = myDAG1.addTerminalEdge(to, symbolStore.getID("NUM"), symbolStore.getID("PL"));
    // add edge to AGR target GEN=M
    to = myDAG1.addTerminalEdge(to, symbolStore.getID("GEN"), symbolStore.getID("M"));
    // add to ROOT a node TNS=PAST
    to = myDAG1.addTerminalEdge(myDAG1.rootNodeId, symbolStore.getID("TNS"), symbolStore.getID("PAST"));
    //
    to = myDAG1.addTerminalEdge(myDAG1.rootNodeId, symbolStore.getID("ASP"), symbolStore.getID("PERF"));

    myDAG1.saveDOTtoFile("out.dot");
    //for (auto const &x : myDAG1.pathValue) {
    //    cout << x.first.first << " " << x.first.second << " " << DAG::symbolStore.getLabel(x.second) << endl;
    //}
    //cout << endl;

    cout << myDAG1.getDOT() << endl;

    to = myDAG2.addEdge(myDAG2.rootNodeId, symbolStore.getID("AGR"));
    // add edge to AGR target NUM=PL
    to = myDAG2.addTerminalEdge(to, symbolStore.getID("NUM"), symbolStore.getID("PL"));
    // add to ROOT a node TNS=PAST
    to = myDAG2.addTerminalEdge(myDAG2.rootNodeId, symbolStore.getID("ANIM"), symbolStore.getID("+"));

    DAG tmpDAG = myDAG1.unify(myDAG2);
    cout << tmpDAG.getDOT() << endl;

    to = myDAG3.addEdge(myDAG3.rootNodeId, symbolStore.getID("AGR"));
    // add edge to AGR target NUM=PL
    to = myDAG3.addTerminalEdge(to, symbolStore.getID("NUM"), symbolStore.getID("SG"));
    // add to ROOT a node TNS=PAST
    to = myDAG3.addTerminalEdge(myDAG3.rootNodeId, symbolStore.getID("TNS"), symbolStore.getID("PAST"));
    //
    to = myDAG3.addTerminalEdge(myDAG3.rootNodeId, symbolStore.getID("ASP"), symbolStore.getID("PRES"));

    tmpDAG = myDAG1.unify(myDAG3);
    cout << tmpDAG.getDOT() << endl;

}

int main() {

    test();
    return 0;
}