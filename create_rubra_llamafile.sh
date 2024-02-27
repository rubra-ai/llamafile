gmake -j8 && sudo gmake install PREFIX=/usr/local

# download model if it hasn't been downloaded yet
if [ ! -f "openhermes-2.5-neural-chat-v3-3-slerp.Q6_K.gguf" ]; then
    wget "https://huggingface.co/TheBloke/OpenHermes-2.5-neural-chat-v3-3-Slerp-GGUF/resolve/main/openhermes-2.5-neural-chat-v3-3-slerp.Q6_K.gguf"
fi

# copy the base llamafile
cp /usr/local/bin/llamafile rubra.llamafile
cp .args_llm .args
# package everything up
zipalign -j0 \
  rubra.llamafile \
  openhermes-2.5-neural-chat-v3-3-slerp.Q6_K.gguf \
  .args

rm .args

## run it
# ./rubra.llamafile
