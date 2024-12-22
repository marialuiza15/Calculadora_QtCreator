#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QVBoxLayout>
#include <QRegularExpression>
#include <QFont>

// Funções globais para a lógica da calculadora
static double valorAtual = 0;
static QString operacaoAtual = "";
static int novaEntrada = 1; // Controla quando limpar o campo para nova entrada

// Atualiza o display da calculadora
void atualizarDisplay(QLineEdit *display, const QString *texto) {
    display->setText(*texto);
}

// Quando um botão numérico é clicado
void numeroClicado(QLineEdit *display, int valor) {
    if (novaEntrada) {
        display->clear();
        novaEntrada = 0;
    }
    display->setText(display->text() + QString::number(valor));
}

// Quando uma operação é clicada
void operacaoClicada(QLineEdit *display, const QString *operacao) {
    valorAtual = display->text().toDouble();
    operacaoAtual = *operacao;
    novaEntrada = 1;
}

// Quando o botão "=" é clicado
void calcularResultado(QLineEdit *display) {
    double novoValor = display->text().toDouble();

    if (operacaoAtual == "+") {
        valorAtual += novoValor;
    } else if (operacaoAtual == "-") {
        valorAtual -= novoValor;
    } else if (operacaoAtual == "x") {
        valorAtual *= novoValor;
    } else if (operacaoAtual == "÷") {
        if (novoValor != 0) {
            valorAtual /= novoValor;
        } else {
            display->setText("Erro: Divisão por zero");
            return;
        }
    }

    display->setText(QString::number(valorAtual));
    operacaoAtual = "";
    novaEntrada = 1;
}

// Quando o botão "C" é clicado
void limpar(QLineEdit *display) {
    valorAtual = 0;
    operacaoAtual = "";
    display->setText("0");
    novaEntrada = 1;
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Janela principal
    QWidget *janela = new QWidget;
    QFont fonteDisplay("Arial", 18, QFont::Bold);
    janela->setFont(fonteDisplay);
    janela->setWindowTitle("Calculadora em C :)");

    janela->setStyleSheet(
        "QWidget {"
        "   background-color: #FFFDEC;" // Cor de fundo
        "}"

        "QLineEdit {"
        "   font-size: 22px;" // Tamanho da fonte no display
        "   background-color: #FFFFFF;" // Fundo branco
        "   color: #86A788;" // Texto cinza escuro
        "   border: 2px solid #86A788;" // Borda cinza
        "   border-radius: 5px;" // Bordas arredondadas
        "   padding: 5px;" // Espaçamento interno
        "}"

        "QPushButton {"
        "   font-size: 16px;" // Tamanho da fonte nos botões
        "   background-color: #FFE2E2;" // Cor do botão
        "   color: #388E3C;" // Cor do texto
        "   border: 1px solid #388E3C;" // Borda verde escuro
        "   border-radius: 5px;" // Bordas arredondadas
        "   padding: 10px;" // Espaçamento interno
        "}"

        "QPushButton:pressed {"
        "   background-color: #45a049;" // Cor ao clicar
        "}"

        "QPushButton:hover {"
        "   background-color: #66BB6A;" // Cor ao passar o mouse
        "}"
        );

    // Layout principal
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(janela);

    // Display
    QLineEdit *display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMinimumHeight(50);
    layoutPrincipal->addWidget(display);

    // Layout dos botões
    QGridLayout *layoutBotoes = new QGridLayout;
    QString botoes[4][4] = {
        {"7", "8", "9", "+"},
        {"4", "5", "6", "-"},
        {"1", "2", "3", "*"},
        {"C", "0", "=", "/"}
    };

    // Adicionando os botões
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            QPushButton *botao = new QPushButton(botoes[i][j]);
            layoutBotoes->addWidget(botao, i, j);

            if (botoes[i][j].contains(QRegularExpression("[0-9]"))) {
                // Botões numéricos
                QObject::connect(botao, &QPushButton::clicked, [=]() {
                    numeroClicado(display, botoes[i][j].toInt());
                });
            } else if (botoes[i][j] == "+" || botoes[i][j] == "-" || botoes[i][j] == "*" || botoes[i][j] == "/") {
                // Operações
                QObject::connect(botao, &QPushButton::clicked, [=]() {
                    operacaoClicada(display, &botoes[i][j]);
                });
            } else if (botoes[i][j] == "=") {
                // Resultado
                QObject::connect(botao, &QPushButton::clicked, [=]() {
                    calcularResultado(display);
                });
            } else if (botoes[i][j] == "C") {
                // Limpar
                QObject::connect(botao, &QPushButton::clicked, [=]() {
                    limpar(display);
                });
            }
        }
    }

    layoutPrincipal->addLayout(layoutBotoes);
    janela->setLayout(layoutPrincipal);
    janela->show();

    return app.exec();
}
