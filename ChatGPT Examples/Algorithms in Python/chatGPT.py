import torch
import transformers

# Load a pre-trained GPT-2 model
model = transformers.GPT2Model.from_pretrained('gpt2')

# Set the model to eval mode (necessary for generating text)
model.eval()

# Define a function for generating responses to input text
def generate_response(input_text, model, device):
  # Encode the input text as input for the model
  input_ids = torch.tensor(tokenizer.encode(input_text)).unsqueeze(0).to(device)

  # Generate a response by prompting the model to predict the next token
  output = model(input_ids, labels=input_ids)
  prediction_scores, prediction_tokens = output[:2]

  # Concatenate the predicted tokens to generate the response
  response = tokenizer.decode(prediction_tokens[0], skip_special_tokens=True)
  return response

# Define a device (e.g. GPU or CPU) to run the model on
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

# Define a tokenizer to preprocess the text
tokenizer = transformers.GPT2Tokenizer.from_pretrained('gpt2')

# Use the model to generate a response to an input message
input_text = "Hello, how are you today?"
response = generate_response(input_text, model, device)
print(response)
