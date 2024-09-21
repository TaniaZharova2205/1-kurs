#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>
#include <stdio.h>
#include <stdlib.h>


#define REDRAWALL 1
#define INVERTALL 2
#define TOZERO 3

typedef struct cell{
    Window window;
    unsigned long color;
} cell;

static  Display  *dpy;  		/*  Адрес  дисплейной  структуры */
static GC gc;                   /*графический интерфейс*/
static  Window  desk;  			/*  Окно  игрового  поля  программы */
static  int  X0=0;  			/*  Начальные  координаты  окна */
static  int  Y0=0;  			/*  программы  на  экране */

static unsigned ROWS; 		/* Число рядов клеток */
static unsigned COLS; 		/* Число клеток ряда */
static unsigned SIZE;       /* Размер клетки */
static cell** box; 		    /* Адрес массива NYxNX клеток */

static unsigned long color[2];

/*  Настройка  графических  параметров */

int  xcustom()  {
    int  x,  y;  /*  Позиции  окон */
    unsigned  w,  h;  /*  Габариты  окон */
    int  depth  =  DefaultDepth(dpy,  0);  /*  Глубина  экрана  0  */
    Window  root;  /*  Корневое  окно  экрана  */
    XSetWindowAttributes  attr;  /*  Атрибуты  окон */
    unsigned  long  amask;  /*  Маска  оконных  атрибутов */
    XSizeHints  hint;  /*  Геометрия  оконного  менеджмента */
    int  i,  j;  /*  индексы  окон */
    Colormap colormap;

/*  Настройка  графических  контекстов */

    root  =  DefaultRootWindow(dpy);  /*  Корневое  окно  экрана */
    gc = XCreateGC(dpy, root, 0, NULL);

/*настройка цветов*/
    colormap = XDefaultColormap(dpy, DefaultScreen(dpy));
    XColor RGBpixel;
    XParseColor(dpy, colormap, "#ffffff", &RGBpixel);       //white
    XAllocColor(dpy, colormap, &RGBpixel);
    color[0] = RGBpixel.pixel;
    XParseColor(dpy, colormap, "#000000", &RGBpixel);       //black
    XAllocColor(dpy, colormap, &RGBpixel);
    color[1] = RGBpixel.pixel;
/*настройка цветов*/


/*  Настройка  игрового  окна  программы */
    attr.override_redirect  =  False;   /*  WM  обрамление  окна */
    attr.background_pixel  =  color[0]; //0xFFFFFF;  /*  white  */
    amask  =  (CWOverrideRedirect  |  CWBackPixel);
    w  = COLS * SIZE;    /*  Габариты */
    h  = ROWS * SIZE;    /*  игрового  окна */
    x  =  X0;  y  =  Y0;  /*  Начальные  координаты  окна  игры */
    desk  =  XCreateWindow(dpy,  root,  x,  y,  w,  h, 1, depth, InputOutput,
                           CopyFromParent, amask, &attr); /* Геометрические  рекомендации  оконного  менеджера */
    hint.flags  =  (PMinSize  |  PMaxSize  |  PPosition);
    hint.min_width  =  hint.max_width  =  w;  /*  ФИКСИРОВАТЬ */
    hint.min_height  =  hint.max_height  =  h;  /*  габариты  и */
    hint.x  =  x;  hint.y  =  y; /*  позицию  окна  игрового  поля */
    XSetNormalHints(dpy,  desk,  &hint);  /*  в  свойстве  WM  */
    XStoreName(dpy,  desk,  "xpict");  /*  Заголовок  окна */


/*  Настройка  окон  клеток  */
    amask  =  CWOverrideRedirect  |  CWBackPixel  |  CWEventMask;
    attr.override_redirect = True;      /* Отмена обрамления окна */
    attr.background_pixel = color[0];
    attr.event_mask  =  (KeyPressMask  |  ExposureMask | ButtonPressMask);
    w = SIZE;
    h = SIZE;  /*  Габариты  окна  клетки */
    x = 0;
    y = 0;
    box = (cell **)calloc(ROWS, sizeof(cell*));
    for(i = 0; i < ROWS; i++) { /*  Цикл  по  рядам  клеток */
        box[i] = (cell *) calloc(COLS, sizeof(cell));
        x = 0;
        for (j = 0; j < COLS; j++) { /* Создать окна клеток */
            box[i][j].window = XCreateWindow(dpy, desk, x, y, w, h, 0, depth,
                                      InputOutput, CopyFromParent, amask,
                                      &attr);/*  Отображение  всех  окон  на  экране */
            box[i][j].color = 0;
            x += SIZE;
        }
        y += SIZE;
    }

/*создание окон*/
    XMapWindow(dpy,  desk);
    XMapSubwindows(dpy,  desk);
    return(0);
}

/*  xcustom  */

/*функция перекраски 1 пиктограммы по нажатию мыши*/
int  repaint(XEvent*  ev)  {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
        {
            if (box[i][j].window == ev->xbutton.window)
            {
                box[i][j].color = (1 == box[i][j].color) ? 0 : 1;
                XSetForeground(dpy, gc, color[box[i][j].color]);
                XFillArc(dpy, box[i][j].window, gc, 0, 0, SIZE, SIZE, 0, 360*64);
            }
        }
    return 0;
}  /*  repaint  */


/*изменение цвета в окнах глобально*/
int  redraw(short type)  {
    switch (type){
        case (REDRAWALL):
            break;
        case (TOZERO): {
            for (int i = 0; i < ROWS; i++)
                for (int j = 0; j < COLS; j++) {
                    box[i][j].color = 0;
                }
            break;
        }
        case (INVERTALL):{
            for (int i = 0; i < ROWS; i++)
                for (int j = 0; j < COLS; j++) {
                    box[i][j].color = (box[i][j].color == 1) ? 0 : 1;
                }
            break;
        }
    }

    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
        {
            XSetForeground(dpy, gc, color[box[i][j].color]);
            XFillArc(dpy, box[i][j].window, gc, 0, 0, SIZE, SIZE, 0, 360*64);
        }
    return 0;
}

/*обработка событий нажатия на клавиши*/
int  key_analiz(XEvent*  ev){
    if (ev->xkey.keycode == XKeysymToKeycode(dpy, XK_Escape)) {
        redraw(TOZERO);
        return 0;
    }
    if ((ev->xkey.keycode == XKeysymToKeycode(dpy, XK_Alt_R)) || (ev->xkey.keycode == XKeysymToKeycode(dpy, XK_Alt_L))) {
        redraw(INVERTALL);
        return 0;
    }
    if ((ev->xkey.keycode == XKeysymToKeycode(dpy, XK_q)) || (ev->xkey.keycode == XKeysymToKeycode(dpy, XK_Q)))
        return 1;
    return 0;
}

int  dispatch()  {  /*  Диспетчер  событий */
    XEvent  event;  /*  Структура  событий */
    int  done  =  0;  /*  Флаг  выхода */
    while(done  ==  0)  {  /*  Цикл  обработки  событий */
        XNextEvent(dpy,  &event);  /*  Чтение  событий */
        switch(event.type)  {
            case  Expose:
                redraw(REDRAWALL);  /*  Перерисовка */
                break;
            case  ButtonPress:
                repaint(&event);    /*перекраска региона*/
                break;
            case  KeyPress:
                done  =  key_analiz(&event);    /*проверка условий нажатий на клавиши*/
                break;
            default:  break;
        }  /*  switch  */
    } /* while */
    return(0);
}  /*  dispatch  */



/*освобождение памяти выделенной для массивов окон*/
int free_custom(){
    for ( int i = 0; i < ROWS; i++)
        free(box[i]);
    free(box);
    return 0;
}


int main(int argc, char* argv[]) {
    if(argc  !=  4) {
        fprintf(stderr, "Default:  a.out 100 10 10\n");
        SIZE = 100;
        ROWS = 10;
        COLS = 10;
    }
    else{
        SIZE = atoi(argv[1]);   //дефолтные значения
        ROWS = atoi(argv[2]);   //дефолтные значения
        COLS = atoi(argv[3]);   //дефолтные значения
    }


    dpy  =  XOpenDisplay(NULL);
    xcustom();
    dispatch();
    XDestroySubwindows(dpy,  desk);
    XDestroyWindow(dpy,  desk);
    free_custom();
    XCloseDisplay(dpy);
    return(0);
} /* main */
