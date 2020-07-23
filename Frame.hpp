#ifndef _FRAME_HPP_
#define _FRAME_HPP_
#include <iostream>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

class Frame {
    private:
        int frame_pointer;
        vector<tuple<string, int>> variaveis;
        vector<tuple<string, int>> parametros;
        int contador;
    public:
        void AtribuiID(string str_id);
        void AtribuiParam(string str_param);
        int get_posicao(string str_var);
        void AtribuiParamChamada(string str);
        int get_tamanho_do_frame();
        int get_posicao_frame_pointer_anterior();
        Frame();

};

#endif