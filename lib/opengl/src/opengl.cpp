/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** OOP_arcade_2019,
*/

#include <fcntl.h>
#include "opengl.hpp"

extern "C" IGraphicalModule *newInstance()
{
    return new opengl();
}

extern "C" void destroyInstance(IGraphicalModule *opengl)
{
    delete opengl;
}

opengl::opengl()
{
}

opengl::~opengl()
{
}

/* Display */

void opengl::createWindow(int x, int y, int &ac, char **av)
{
    _windowSize.first = x;
    _windowSize.second = y;

    glutInit(&ac, av);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(x, y);
    glutInitWindowPosition(0/*(1920 - x) / 2*/, 0);
    glutCreateWindow("Arcade");
    gluOrtho2D(0, x, 0, y);
    glClearColor(0, 0, 0, 0);
    glColor3f(1.0, 1.0, 1.0);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardSpecial);
    glutDisplayFunc(displayUnused);
    _coef = 1;

    std::vector<std::string> devices;

    if (!InitOpenAL())
        throw std::exception();

    GetDevices(devices);
}

void opengl::closeWindow()
{
    glutDestroyWindow(glutGetWindow());
    glutMainLoopEvent();
    glutExit();
    ShutdownOpenAL();
}

void opengl::display()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glFlush();
    glutPostRedisplay();
}

void opengl::drawFramebuffer(std::vector<std::vector<color_t>> bf)
{
    _coef = 1;
    while (static_cast<int>(bf.size()) > _windowSize.second &&
        static_cast<int>(bf.at(0).size()) > _windowSize.first) {
        reduceMe(bf);
        _coef *= 2;
    }

    glBegin(GL_POINTS);

    for (int j = 0; j < _windowSize.second; ++j) {
        for (int i = 0; i < _windowSize.first; ++i) {
            glColor3f(0, 0, 0);
            glPointSize(1);
            glVertex2i(i, _windowSize.second - j);
        }
    }
    for (int j = 0; (j < static_cast<int>(bf.size()) || j < _windowSize.second) && j < _windowSize.second; ++j) {
        for (int i = 0; (i < static_cast<int>(bf.at(0).size()) || i < _windowSize.first) && i < _windowSize.first; ++i) {
            j < static_cast<int>(bf.size()) && i < static_cast<int>(bf.at(0).size()) ? glColor3f(static_cast<float>(bf.at(j).at(i).r) / 255.0f, static_cast<float>(bf.at(j).at(i).g) / 255.0f, static_cast<float>(bf.at(j).at(i).b) / 255.0f) : glColor3f(0, 0, 0);
            glPointSize(1);
            glVertex2i(i + (_windowSize.first / 2 - bf.at(0).size() / 2), _windowSize.second - j - (_windowSize.second / 2 - bf.size() / 2));
        }
    }
    glEnd();
}

void opengl::drawText(text_t t)
{
/*    glColor3f(static_cast<float>(t._color.r) / 255.0f, static_cast<float>(t._color.g) / 255.0f, static_cast<float>(t._color.b) / 255.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 2500, 0, 2500);
    glPushMatrix();

    glRotatef(0, 0.0, 0.0, 1.0);
    glTranslatef(-700, 0, 0);

//    glScalef(0.45,0.45,0);


    if (t._anchor.second == 1)
        glTranslatef(t._pos.first, _windowSize.second - t._pos.second - glutStrokeWidth(GLUT_STROKE_ROMAN, 'P'), 0);
    if (t._anchor.second == 0)
        glTranslatef(t._pos.first, static_cast<float>(_windowSize.second) - t._pos.second - (static_cast<float>(glutStrokeWidth(GLUT_STROKE_ROMAN, 'A')) / 2), 0);
    if (t._anchor.first == 1)
        glTranslatef(t._pos.first - glutStrokeLength(GLUT_STROKE_ROMAN,
            reinterpret_cast<const unsigned char *>(t._text.data())), _windowSize.second - t._pos.second, 0);
    if (t._anchor.first == 0)
        glTranslatef(t._pos.first - (static_cast<float>(glutStrokeLength(GLUT_STROKE_ROMAN,
            reinterpret_cast<const unsigned char *>(t._text.data()))) / 2), _windowSize.second - t._pos.second, 0);
*/
/*getInpu

    glutStrokeString(GLUT_STROKE_ROMAN, reinterpret_cast<const unsigned char *>(t._text.data()));
    glPopMatrix();
    glutSwapBuffers();
    glutBitmapString(GLUT_STROKE_ROMAN, reinterpret_cast<const unsigned char *>(t._text.data()));*/
/*

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

    FT_Face face;
    if (FT_New_Face(ft, "games/assets/cyprien_menu_arial.ttf", 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

    FT_Set_Pixel_Sizes(face, 0, 48);

    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;

    FT_GlyphSlot g = face->glyph;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

    for (GLubyte c = 0; c < 128; c++)
    {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use

    }*/

    glPushMatrix();

    /*
     * 0.13 = 18
     * 0.35 = 48
     */

    t._fontSize /= _coef;
    t._pos.first /= _coef;
    t._pos.second /= _coef;
    float coef = 0.00733333 * t._fontSize - 0.00199984;
    std::pair<int, int> pos = t._pos;

    if (t._anchor.second == 1)
        pos.second += glutStrokeWidth(GLUT_STROKE_ROMAN, 'A') * coef;
    if (t._anchor.second == 0)
        pos.second += ((static_cast<float>(glutStrokeWidth(GLUT_STROKE_ROMAN, 'A')) / 2) * coef);
    if (t._anchor.first == 1)
        pos.first -= glutStrokeLength(GLUT_STROKE_ROMAN, reinterpret_cast<const unsigned char *>(t._text.data())) * coef;
    if (t._anchor.first == 0)
        pos.first -= (static_cast<float>(glutStrokeLength(GLUT_STROKE_ROMAN, reinterpret_cast<const unsigned char *>(t._text.data()))) / 2 * coef);

    glTranslatef(pos.first, _windowSize.second - pos.second,0);

    glScalef(coef, coef, 0);
    glLineWidth(coef * 9);
    glColor3f(static_cast<float>(t._color.r) / 255.0f, static_cast<float>(t._color.g) / 255.0f, static_cast<float>(t._color.b) / 255.0f);

    glutStrokeString(GLUT_STROKE_ROMAN, reinterpret_cast<const unsigned char *>(t._text.data()));
    glPopMatrix();
}

size_t opengl::getSmoothness() const
{
    return 1;
}

/* Input */

char opengl::getInput() const
{
    glutMainLoopEvent();
    char key = static_cast<char>(_key);
    _key = -1;
    return (key);
}

/* Sound */

void opengl::stopSound(std::string sound)
{
    sound = sound + std::string(".wav");

    alSourceStop(_sounds[sound].first);

        // Destruction du tampon
    //alDeleteBuffers(1, &_sounds[sound].second);

        // Destruction de la source
    alSourcei(_sounds[sound].first, AL_BUFFER, 0);
    alDeleteSources(1, &_sounds[sound].first);

        // Définition de la position de l'écouteur (ici l'origine)
    // alListener3f(AL_POSITION, 0.f, 0.f, 0.f);

        // Définition de la vitesse de l'écouteur (ici nulle)
    // alListener3f(AL_VELOCITY, 0.f, 0.f, 0.f);

        // Définition de l'orientation de l'écouteur (ici il regarde vers l'axe des Z)
    // ALfloat Orientation[] = {0.f, 0.f, 1.f, 0.f, 1.f, 0.f};
    // alListenerfv(AL_ORIENTATION, Orientation);*/

    _sounds.erase(sound);
}

void opengl::ShutdownOpenAL()
{
    // Récupération du contexte et du device
    ALCcontext* Context = alcGetCurrentContext();
    ALCdevice*  Device  = alcGetContextsDevice(Context);

    // Désactivation du contexte
    alcMakeContextCurrent(NULL);

    // Destruction du contexte
    alcDestroyContext(Context);

    // Fermeture du device
    alcCloseDevice(Device);
}

bool opengl::InitOpenAL()
{
    // Ouverture du device

    ALCdevice* Device = alcOpenDevice(NULL);
    if (!Device)
        return false;

    // Création du contexte
    ALCcontext* Context = alcCreateContext(Device, NULL);
    if (!Context)
        return false;

    // Activation du contexte
    return alcMakeContextCurrent(Context) != 0;
}

void opengl::GetDevices(std::vector<std::string>& Devices)
{
    // Vidage de la liste
    Devices.clear();

    // Récupération des devices disponibles
    const ALCchar* DeviceList = alcGetString(NULL, ALC_DEVICE_SPECIFIER);

    if (DeviceList)
    {
        // Extraction des devices contenus dans la chaîne renvoyée
        while (strlen(DeviceList) > 0) {
            Devices.push_back(DeviceList);
            DeviceList += strlen(DeviceList) + 1;
        }
    }
}

ALuint LoadSound(const std::string& Filename)
{
    // Ouverture du fichier audio avec libsndfile
    SF_INFO FileInfos;
    SNDFILE* File = sf_open(Filename.c_str(), SFM_READ, &FileInfos);
    if (!File)
        return 0;

    // Lecture du nombre d'échantillons et du taux d'échantillonnage (nombre d'échantillons à lire par seconde)
    ALsizei NbSamples  = static_cast<ALsizei>(FileInfos.channels * FileInfos.frames);
    ALsizei SampleRate = static_cast<ALsizei>(FileInfos.samplerate);

    // Lecture des échantillons audio au format entier 16 bits signé (le plus commun)
    std::vector<ALshort> Samples(NbSamples);
    if (sf_read_short(File, &Samples[0], NbSamples) < NbSamples)
        return 0;

    // Fermeture du fichier
    sf_close(File);

    // Détermination du format en fonction du nombre de canaux
    ALenum Format;
    switch (FileInfos.channels) {
        case 1 :  Format = AL_FORMAT_MONO16;   break;
        case 2 :  Format = AL_FORMAT_STEREO16; break;
        default : return 0;
    }

    // Création du tampon OpenAL
    ALuint Buffer;
    alGenBuffers(1, &Buffer);

    // Remplissage avec les échantillons lus
    alBufferData(Buffer, Format, &Samples[0], NbSamples * sizeof(ALushort), SampleRate);

    // Vérification des erreurs
    if (alGetError() != AL_NO_ERROR)
        return 0;

    return Buffer;
}

void opengl::playSound(std::string sound)
{
    ALint Status;
    sound += std::string(".wav");

    if (!exists(sound))
        return;
    if (isInMapInd(_sounds, sound)) {
        alGetSourcei(_sounds[sound].first, AL_SOURCE_STATE, &Status);
        if (Status == AL_PLAYING)
            return;
    }
    ALuint Source;
    unsigned long idx;
    if (isInMapInd(_sounds, sound))
        idx = distance(_sounds.begin(), _sounds.find(sound)) + 1;
    else
        idx = _sounds.size() + 1;
    alGenSources(idx, &Source);
    auto Buffer = LoadSound(sound);
    alSourcei(Source, AL_BUFFER, Buffer);
    alSourcePlay(Source);
    _sounds[sound] = std::make_pair(Source, Buffer);
}

void opengl::setVolume(std::string sound, float volume)
{
    std::string s = sound + std::string(".wav");

    alSourcef(_sounds[s].first, AL_GAIN, static_cast<ALfloat>(volume));
}

float opengl::getVolume(std::string sound __attribute__((unused))) const
{
    return 0;
}

void opengl::stopAllSounds()
{
    while (!_sounds.empty())
        for (auto &e : _sounds) {
            stopSound(e.first.substr(0, e.first.size() - 4));
            break;
    }
}

void displayUnused(void)
{
}

void keyboard(unsigned char touche, int x __attribute__((unused)), int y __attribute__((unused)))
{
    if (touche == 27)
        _key = 1;
    else if (touche == 8)
        _key = 2;
    else if (touche == 13)
        _key = 3;
    else
        _key = touche;
}

void keyboardSpecial(int touche, int x __attribute__((unused)), int y __attribute__((unused)))
{
    _key = -1;
    int input[] = {100, 101, 102, 103, 27};
    int output[] = {5,  7,   6,   8,   1};
    int size = 6;

    for (int i = 0; i < size; ++i)
        if (touche == input[i])
            _key = output[i];
}

void opengl::reduceMe(std::vector<std::vector<color_t>> &bf)
{
    for (int j = 0; j < static_cast<int>(bf.size()); ++j) {
        bf.erase(bf.begin() + j);
        for (int i = 0; i < static_cast<int>(bf.at(0).size()); ++i)
            bf.at(j).erase(bf.at(j).begin() + i);
    }
}

bool opengl::exists(const std::string &name)
{
    return (access(name.c_str(), F_OK) != -1);
}