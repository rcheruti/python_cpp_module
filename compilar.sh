set -e

echo '--- Excluindo anteriores...'
rm -rf ./build
echo '--- Compilando...'
py setup.py build
echo '--- Instalando...'
py setup.py install

echo ''
echo '--- Executar:'
py teste.py
