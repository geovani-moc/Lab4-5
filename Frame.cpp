#include "Frame.hpp"

void Frame::AtribuiID(string str_id) {
    tuple<string, int> temporario;
    get<0>(temporario) = str_id;
    get<1>(temporario) = (-16) - (8 * ((int)variaveis.size()));
    cout << "Adicionado ["<< str_id << "] em ["<<((-16) - (8 * ((int)variaveis.size())))<<"]" << endl;
    variaveis.push_back(temporario);
}

void Frame::AtribuiParam(string str_param) {
    tuple<string, int> temporario;
    get<0>(temporario) = str_param;
    get<1>(temporario) = (+16) + (8 * ((int)parametros.size()));
    cout << "Adicionado ["<< str_param << "] em ["<<((+16) + (8 * ((int)parametros.size())))<<"]" << endl;
    parametros.push_back(temporario);
}

int Frame::get_posicao(string str_var) {
    int tamanho = variaveis.size();
    for (int i = 0; i < tamanho; i++)
    {
        if (get<0>(variaveis[i]) == str_var) return get<1>(variaveis[i]);
    }

    tamanho = parametros.size();
    for (int i = 0; i < tamanho; i++)
    {
        if (get<0>(parametros[i]) == str_var) return get<1>(parametros[i]);
    }

    cerr << "\nErro: varivavel ou parametro nao encontrada no frame." << endl;
}

int Frame::get_tamanho_do_frame() {
    return 8 * (int)(3 + variaveis.size());
}

void Frame::AtribuiParamChamada(string str) {
    AtribuiID(str);
}

Frame::Frame() {
    contador = 0;
    frame_pointer = 0;
}

int Frame::get_posicao_frame_pointer_anterior(){
    return frame_pointer;
}