set hls ic is scs ru nu ls=2 so=7 bs=2 ai cin noswf aw ar sr ts=2 sw=2 mouse=a
syn on
no ; :
nn U <c-r>
no <bs> :noh<cr>
no <space>a ggVG
no <f2> :vs in.txt<cr>
no <f9> :!make %:r<cr>
no <f5> :!time ./%:r < in.txt<cr>
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \| md5sum \| cut -c-8
