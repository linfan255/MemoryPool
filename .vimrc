set nu
syntax on
set confirm

set tabstop=4
set shiftwidth=4
set expandtab
set smarttab

set autoread
set cindent

set tags=tags;
set autochdir

set autoindent
set smartindent
set hlsearch
set background=dark
set showmatch
set ruler
set nocompatible
set backspace=indent,eol,start
set laststatus=2
autocmd InsertLeave * se nocul
autocmd InsertEnter * se cul
set showcmd
set fillchars=vert:/

set fillchars=stl:/

set fillchars=stlnc:/
nmap <F2> :NERDTree  <CR>

set fileencodings=utf-8,ucs-bom,gb18030,gbk,gb2312,cp936
set termencoding=utf-8
set encoding=utf-8

inoremap ' ''<ESC>i
inoremap " ""<ESC>i

inoremap ( ()<ESC>i
inoremap ) <c-r>=ClosePair(')')<CR>

inoremap [ []<ESC>i
inoremap ] <c-r>=ClosePair(']')<CR>

inoremap { {}<ESC>i
inoremap } <c-r>=ClosePair('}')<CR>
imap {<CR> {<CR>}<ESC>O

function! ClosePair(char)
    if getline('.')[col('.') - 1] == a:char
        return "\<Right>"
    else
        return a:char
    endif
endfunction


func SkipPair()
    if getline('.')[col('.') - 1] == ')' || getline('.')[col('.') - 1] == ']' || getline('.')[col('.') - 1] == '"' || getline('.')[col('.') - 1] == "'" || getline('.')[col('.') - 1] == '}'
        return "\<ESC>la"
    else
        return "\t"
    endif
endfunc
inoremap <TAB> <c-r>=SkipPair()<CR>

